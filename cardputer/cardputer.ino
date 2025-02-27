#include "M5Cardputer.h"
#include "rtx_manager.h"
#include <random>

#define PREVIEW_DOWNSCALE 6

RTXManager rtx;
bool screenSaver = false;

char *format_scratch;
char *format_text(const char *format, ...)
{
  free(format_scratch);

  va_list args;

  va_start(args, format);
  if (0 > vasprintf(&format_scratch, format, args))
    format_scratch = NULL; // this is for logging, so failed allocation is not fatal
  va_end(args);

  if (format_scratch)
  {
    return format_scratch;
  }
  else
  {
    return "uh oh";
  }
}

void drawAxes(int cx, int cy, int size)
{
  vec3 up = rtx.cam.transform.up;
  vec3 right = rtx.cam.transform.right;
  vec3 forwards = rtx.cam.transform.forwards;
  M5Cardputer.Display.drawLine(cx, cy, cx + size * right.x, cy - size * right.y, TFT_RED);
  M5Cardputer.Display.drawLine(cx, cy, cx + size * up.x, cy - size * up.y, TFT_GREEN);
  M5Cardputer.Display.drawLine(cx, cy, cx + size * forwards.x, cy - size * forwards.y, TFT_BLUE);
}

void setup()
{
  Serial.begin(921600);
  Serial.println("hi");

  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);

  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(TFT_WHITE);
  // M5Cardputer.Display.setTextDatum(left);
  M5Cardputer.Display.setTextFont(&fonts::AsciiFont8x16);
  M5Cardputer.Display.setTextSize(1);

  rtx = makeRTXManager(240, 135);
  rotateTransform(&rtx.cam.transform, VEC_X, -0.3);
}

void drawPreview()
{
  unsigned long startT = millis();
  RTXResetRender(&rtx);
  rtx.config.raysPerPixel = 2;
  rtx.config.maxBounces = 4;
  // todo: draw every other pixel in 2 passes
  for (int y = 0; y < rtx.height; y += PREVIEW_DOWNSCALE)
  {
    for (int x = 0; x < rtx.width; x += PREVIEW_DOWNSCALE)
    {
      RGB rgb = RTXRenderPixel(&rtx, x, y, (RGB){0, 0, 0}, 1.0);
      auto color = M5Cardputer.Display.color888(rgb.r, rgb.g, rgb.b);
      M5Cardputer.Display.fillRect(x, y, PREVIEW_DOWNSCALE, PREVIEW_DOWNSCALE, color);
    }
  }
  rtx.currentSamples++;
  drawAxes(240 / 2, 135 / 2, 20);
  unsigned long endT = millis();
  M5Cardputer.Display.drawString(format_text("%ums", endT - startT), 0, 0);
}

void drawNormal()
{
  unsigned long start = millis();
  rtx.config.raysPerPixel = 1;
  rtx.config.maxBounces = 8;
  // todo: draw every other pixel in 2 passes
  RTXRender(&rtx);
  if (!screenSaver)
  {
    M5Cardputer.Display.setBrightness(100);
    for (int y = 0; y < rtx.height; y++)
    {
      for (int x = 0; x < rtx.width; x++)
      {
        RGB rgb = rtx.buf1[x + y * rtx.width];
        auto color = M5Cardputer.Display.color888(rgb.r, rgb.g, rgb.b);
        M5Cardputer.Display.fillRect(x, y, 1, 1, color);
      }
    }
  }
  else
  {
    M5Cardputer.Display.clearDisplay(TFT_BLACK);
    M5Cardputer.Display.setBrightness(2);
  }
  unsigned long end = millis();
  M5Cardputer.Display.drawString(format_text("%d", rtx.currentSamples), 0, 0);
  M5Cardputer.Display.drawString(format_text("%u ms", end - start), 0, 12);
}

unsigned long timeSincePreview;
void loop()
{
  // int c = random(255);
  // M5Cardputer.Display.fillRect(0,0,240,135,c);
  // RTXRender(&rtx);
  M5Cardputer.update();
  Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
  bool rerender = false;
  for (char c : status.word)
  {
    if (!screenSaver)
    {

      if (c == 'e')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.forwards, 2.0));
      if (c == 's')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.forwards, -2.0));
      if (c == 'a')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.right, -2.0));
      if (c == 'd')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.right, 2.0));
      if (c == 'w')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.up, 2.0));
      if (c == 'r')
        rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos, vec3Scale(rtx.cam.transform.up, -2.0));
      if (c == ';') // up arrow kinda
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.right, -0.1);
      if (c == '.') // down arrow kinda
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.right, 0.1);
      if (c == ',' || millis % 30000 <= 100) // left arrow kinda
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.up, -0.1);
      if (c == '/' || millis % 60000 <= 100) // right arrow kinda
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.up, 0.1);
      if (c == 'l') // left of the up arrow kinda. rolls left
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.forwards, -0.1);
      if (c == '\'') // right of the up arrow kinda. rolls right
        rotateTransform(&rtx.cam.transform, rtx.cam.transform.forwards, 0.1);
      if (c == '[')
        rtx.cam.fov *= 1.1;
      if (c == ']')
        rtx.cam.fov /= 1.1;
      if ()

      updateCameraFOV(&rtx.cam, rtx.cam.fov);
    }
    rerender = true;
    if (c == 'b')
    {
      rerender = false;
      screenSaver = !status.fn;
    }
  }
  if (rerender)
  {
    drawPreview();
    RTXResetRender(&rtx);
    timeSincePreview = millis();
  }
  if (millis() - timeSincePreview > 1000)
  {
    drawNormal();
  }
}
