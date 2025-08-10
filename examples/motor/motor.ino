#include <Arduino.h>
#include <KN_FAST.h>

void setup() {
  Serial.begin(115200);
  KNSetup();
}

void loop() {

  FW(1000);             // 1. เดินหน้า
  delay(1000);

  BW(1000);             // 2. ถอยหลัง
  delay(1000);

  SL(1000);             // 3. เลี้ยวซ้าย
  delay(1000);

  SR(1000);             // 4. เลี้ยวขวา
  delay(1000);

  TL(1000);             // 5. หมุนซ้าย (เฉพาะมอเตอร์ 2 เดินหน้า)
  delay(1000);

  TR(1000);             // 6. หมุนขวา (เฉพาะมอเตอร์ 1 เดินหน้า)
  delay(1000);

  motor(1, 800);        // มอเตอร์ 1 เดินหน้า
  delay(1000);

  motor(2, -800);       // มอเตอร์ 2 ถอยหลัง
  delay(1000);

  motor2(600, -600);    // Motor 1 เดินหน้า, Motor 2 ถอยหลัง
  delay(1000);

  motorstop(1);         // 9. หยุดมอเตอร์แยกตัว
  delay(500);
  motorstop(2);
  delay(500);

  kn_motor_stop_all();  // 10. หยุดทุกมอเตอร์
  delay(2000);
}
