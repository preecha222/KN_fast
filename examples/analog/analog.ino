#include "KN_fast.h"

void setup() {
  Serial.begin(115200);
  KNSetup();
}

void loop() {
  int analogValue1 = analogRead(1);
  int analogValue2 = analogRead(3); 


  Serial.print("AN1 (GPIO1): ");
  Serial.print(analogValue1);
  Serial.print("  |  AN2 (GPIO3): ");
  Serial.println(analogValue2);

  delay(500); 
}
