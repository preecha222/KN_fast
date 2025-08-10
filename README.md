# KN_fast Library

The **KN_fast** library simplifies motor control and analog reading using:
- **MCP3008** for analog input (up to 16 channels)
- **PCA9685** for PWM output (e.g., motor control)

Designed for use with ESP32 boards.

---

## 📦 Installation

### Method 1 – ZIP Import  
1. Download this library as a `.zip` file  
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library**  
3. Select the downloaded file

### Method 2 – Manual Install  
Unzip this folder into your `Documents/Arduino/libraries/` directory.

---

## 🧪 Example Usage

```cpp
#include <KN_fast.h>

void setup() {
  Serial.begin(115200);
  KNSetup();
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
```