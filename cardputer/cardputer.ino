#include "M5Cardputer.h"

void setup() {
  Serial.begin(921600);
  Serial.println("hi");

  auto cfg = M5.config();
  M5Cardputer.begin(cfg,true);

  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(GREEN);
  // M5Cardputer.Display.setTextDatum(left);
  M5Cardputer.Display.setTextFont(&fonts::AsciiFont8x16);
  M5Cardputer.Display.setTextSize(1);
}

void loop() {

}