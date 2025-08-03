#include "KN_fast.h"

void setup() {
  Serial.begin(115200);
  KNSetup();  // ใช้ setup รวมจาก library
}

void loop() {
  SW_press();  // รอให้กดและปล่อย
  Serial.println("ปุ่มถูกกดแล้วปล่อย");
}
