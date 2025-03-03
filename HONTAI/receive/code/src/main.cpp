#include "M5AtomS3.h"
#include <Arduino.h>
#include "Arduino_de_Serial.h"

Arduino_de_Serial serial;
uint8_t data[11];
int fail = 0;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(115200);
  Serial.println("Ready.");
  AtomS3.Display.setCursor(0, 0);
  AtomS3.Display.setTextSize(1.6); // テキストサイズを2倍に設定
  AtomS3.Display.println("Hello, M5AtomS3R!");
  delay(1000);  // 初期化後の待機
}

void loop() {
  AtomS3.Lcd.fillRect(0, 0, AtomS3.Lcd.width(), AtomS3.Lcd.height(), BLACK);
  if (serial.getSig(data)) {
    fail = 0;
    AtomS3.Display.setCursor(0, 0);
    AtomS3.Display.print("LX:");
    AtomS3.Display.print(data[LX]);
    AtomS3.Display.print("/LY:");
    AtomS3.Display.println(data[LY]);
    AtomS3.Display.print("RX:");
    AtomS3.Display.print(data[R_X]);
    AtomS3.Display.print("/RY:");
    AtomS3.Display.println(data[RY]);
    AtomS3.Display.print("L2:");
    AtomS3.Display.print(data[L2]);
    AtomS3.Display.print("/R2:");
    AtomS3.Display.println(data[R2]);

    if (data[BA1] & SQUARE) AtomS3.Display.println("SQUARE");
    if (data[BA1] & CROSS) AtomS3.Display.println("CROSS");
    if (data[BA1] & CIRCLE) AtomS3.Display.println("CIRCLE");
    if (data[BA1] & TRIANGLE)  AtomS3.Display.println("TRIANGLE");

    if (data[BA1] & UP) AtomS3.Display.println("UP");
    if (data[BA1] & RIGHT) AtomS3.Display.println("RIGHT");
    if (data[BA1] & DOWN) AtomS3.Display.println("DOWN");
    if (data[BA1] & LEFT) AtomS3.Display.println("LEFT");

    if (data[BA2] & L1) AtomS3.Display.println("L1");
    if (data[BA2] & L3) AtomS3.Display.println("L3");
    if (data[BA2] & R1) AtomS3.Display.println("R1");
    if (data[BA2] & R3) AtomS3.Display.println("R3");

    if (data[BA2] & Share) AtomS3.Display.println("Share");
    if (data[BA2] & Options) AtomS3.Display.println("Options");
    if (data[BA2] & PS) AtomS3.Display.println("PS");
  } else {
    fail++;
  }
  if (fail > 10) {
    AtomS3.Display.setCursor(0, 0);
    AtomS3.Display.println("fail");
    delay(50);
  }
  delay(8);
}
