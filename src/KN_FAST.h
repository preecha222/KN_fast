#ifndef KN_FAST_H
#define KN_FAST_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

// ====== กำหนดอุปกรณ์ I2C และ SPI ======
TwoWire I2C_Alt = TwoWire(1);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// ====== กำหนดขา GPIO ======
// I2C
#define I2C1_SDA 4
#define I2C1_SCL 5
#define I2C2_SDA 20
#define I2C2_SCL 21

// SPI
#define SPI_MOSI 6
#define SPI_MISO 7
#define SPI_SCLK 8
#define SPI_CS1   9
#define SPI_CS2  10

// ADC
#define ADC1_PIN 1
#define ADC2_PIN 3

// Button
#define SW_PORT 2

// Motor PWM Channels
#define AIN1_CH 3
#define AIN2_CH 4
#define PWMA_CH 1
#define BIN1_CH 5
#define BIN2_CH 6
#define PWMB_CH 2


// ====== ฟังก์ชัน I2C ======
void kn_init_i2c1() {
  Wire.begin(I2C1_SDA, I2C1_SCL);
}

void kn_init_i2c2() {
  I2C_Alt.begin(I2C2_SDA, I2C2_SCL);
}

// ====== ฟังก์ชัน SPI ======
void kn_init_spi() {
  SPI.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_CS1);
  pinMode(SPI_CS1, OUTPUT);
  pinMode(SPI_CS2, OUTPUT);
  digitalWrite(SPI_CS1, HIGH);
  digitalWrite(SPI_CS2, HIGH);
}

void kn_test_spi(uint8_t cs) {
  digitalWrite(cs, LOW);
  SPI.transfer(0x55);
  digitalWrite(cs, HIGH);
}

// ===== MCP3008 Read =====
int kn_read_mcp3008(uint8_t csPin, uint8_t channel) {
  if (channel > 7) return -1;
  digitalWrite(csPin, LOW);
  SPI.transfer(0x01);
  uint8_t command = 0b10000000 | (channel << 4);
  uint8_t highByte = SPI.transfer(command);
  uint8_t lowByte = SPI.transfer(0x00);
  digitalWrite(csPin, HIGH);
  return ((highByte & 0x03) << 8) | lowByte;
}

int kn_analog_read(uint8_t ch) {
  if (ch > 15) return -1;
  if (ch < 8) return kn_read_mcp3008(SPI_CS1, ch);
  else return kn_read_mcp3008(SPI_CS2, ch - 8);
}


// ====== ฟังก์ชัน ADC ======
int kn_read_adc(uint8_t pin) {
  pinMode(pin, INPUT);
  return analogRead(pin);
}

// ====== ฟังก์ชันมอเตอร์ ======
void kn_motor_init() {
  pwm.begin();
  pwm.setPWMFreq(1000);
  pwm.setPWM(AIN1_CH, 0, 0);
  pwm.setPWM(AIN2_CH, 0, 0);
  pwm.setPWM(PWMA_CH, 0, 0);
  pwm.setPWM(BIN1_CH, 0, 0);
  pwm.setPWM(BIN2_CH, 0, 0);
  pwm.setPWM(PWMB_CH, 0, 0);
}

void motor(int ch, int Pow) {
  uint8_t in1, in2, pwm_ch;
  Pow = constrain(Pow, -4095, 4095);

  if (ch == 1) {
    in1 = AIN1_CH;
    in2 = AIN2_CH;
    pwm_ch = PWMA_CH;
  } else if (ch == 2) {
    in1 = BIN1_CH;
    in2 = BIN2_CH;
    pwm_ch = PWMB_CH;
  } else {
    return;
  }

  if (Pow > 0) {
    pwm.setPWM(in1, 0, 4095);
    pwm.setPWM(in2, 0, 0);
    pwm.setPWM(pwm_ch, 0, Pow);
  } else if (Pow < 0) {
    pwm.setPWM(in1, 0, 0);
    pwm.setPWM(in2, 0, 4095);
    pwm.setPWM(pwm_ch, 0, -Pow);
  } else {
    pwm.setPWM(in1, 0, 0);
    pwm.setPWM(in2, 0, 0);
    pwm.setPWM(pwm_ch, 0, 0);
  }
}


void motor2(int motor_1, int motor_2) {
  motor(1, motor_1);
  motor(2, motor_2);
}

void FW(int _Speed) { motor2(_Speed, _Speed); }
void BW(int _Speed) { motor2(-_Speed, -_Speed); }
void SL(int _Speed) { motor2(-_Speed, _Speed); }
void SR(int _Speed) { motor2(_Speed, -_Speed); }
void TL(int _Speed) { motor2(0, _Speed); }
void TR(int _Speed) { motor2(_Speed, 0); }

void motorstop(uint8_t ch) {
  if (ch == 1) {
    pwm.setPWM(AIN1_CH, 0, 0);
    pwm.setPWM(AIN2_CH, 0, 0);
    pwm.setPWM(PWMA_CH, 0, 0);
  } else if (ch == 2) {
    pwm.setPWM(BIN1_CH, 0, 0);
    pwm.setPWM(BIN2_CH, 0, 0);
    pwm.setPWM(PWMB_CH, 0, 0);
  }
}

void kn_motor_stop_all() {
  pwm.setPWM(AIN1_CH, 0, 0);
  pwm.setPWM(AIN2_CH, 0, 0);
  pwm.setPWM(PWMA_CH, 0, 0);
  pwm.setPWM(BIN1_CH, 0, 0);
  pwm.setPWM(BIN2_CH, 0, 0);
  pwm.setPWM(PWMB_CH, 0, 0);
}

// ====== ฟังก์ชันปุ่มกด ======
bool SW() {
  return digitalRead(SW_PORT);
}

void SW_press() {
  while (!SW());
  while (SW());
}

// ====== ฟังก์ชัน Setup หลัก ======
void KNSetup() {
  kn_init_i2c1();
  kn_init_i2c2();
  kn_init_spi();
  kn_motor_init();
}

#endif
