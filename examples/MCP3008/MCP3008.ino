#include <KN_FAST.h>

void setup() {
  Serial.begin(115200);
  KNSetup(); // เรียก setup ที่กำหนดไว้ใน library
}

void loop() {
  for (int ch = 0; ch < 16; ch++) {
    int val = kn_analog_read(ch);
    Serial.print("CH");
    Serial.print(ch);
    Serial.print(": ");
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();
  delay(1000);
}
