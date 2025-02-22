#include "M5Cardputer.h"
#include "rtx/rtx_manager.h"
#include <random>


RTXManager rtx;

void setup() {
  Serial.begin(921600);
  Serial.println("hi");

  auto cfg = M5.config();
  M5Cardputer.begin(cfg,true);

  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(TFT_WHITE);
  // M5Cardputer.Display.setTextDatum(left);
  M5Cardputer.Display.setTextFont(&fonts::AsciiFont8x16);
  M5Cardputer.Display.setTextSize(1);

  rtx = makeRTXManager(240,135);
}

void loop() {
  // int c = random(255);
  // M5Cardputer.Display.fillRect(0,0,240,135,c);
  RTXRender(&rtx);

  for (int y=0;y<rtx.height;y++) {
    for (int x=0;x<rtx.width;x++) {
      RGB rgb=rtx.buf1[x+y*rtx.width];
      auto color = M5Cardputer.Display.color888(rgb.r,rgb.g,rgb.b);
      M5Cardputer.Display.fillRect(x,y,1,1,color);
    }
  }

}