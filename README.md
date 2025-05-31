
# ESP32 & Arduino UGV Controller

Control a 2-wheel UGV using the Blynk app. An ESP32 handles Wi-Fi/Blynk communication and sends motor commands to an Arduino via serial.

## 🔌 Wiring Guide

**ESP32 <-> Arduino:**
* **ESP32 TX0 (GPIO1)** -> **Arduino RX (Pin 0)**
* **ESP32 RX0 (GPIO3)** -> **Arduino TX (Pin 1)**
* **ESP32 GND** -> **Arduino GND** (Common Ground)

**Arduino -> Motor Driver:**
* **Arduino Pin 4 (`DIR1`)**: Motor 1 Direction
* **Arduino Pin 5 (`PWM1`)**: Motor 1 Speed (PWM)
* **Arduino Pin 7 (`DIR2`)**: Motor 2 Direction
* **Arduino Pin 6 (`PWM2`)**: Motor 2 Speed (PWM)

**Power:**
* Connect ESP32 and Arduino/Motor Driver to appropriate power sources.

*Serial Upload Note:* Disconnect ESP32 TX/RX from Arduino Pins 0/1 when uploading to Arduino.

## 🛠️ Code Configuration

**1. `esp32.ino` (ESP32 Code):**

* **Blynk Credentials (Lines 1-3):**
    * `BLYNK_TEMPLATE_ID`: "YOUR_TEMPLATE_ID"
    * `BLYNK_TEMPLATE_NAME`: "YOUR_PROJECT_NAME"
    * `BLYNK_AUTH_TOKEN`: "YOUR_BLYNK_AUTH_TOKEN"
* **WiFi Credentials (Lines 7-8):**
    * `ssid`: "YOUR_WIFI_SSID"
    * `pass`: "YOUR_WIFI_PASSWORD"
* **UGV Parameters (Optional Adjustments):**
    * `WHEEL_DISTANCE` (Line 13): Distance between wheels in meters (e.g., `0.65`).
    * `MAX_LINEAR_VEL` (Line 15): Expected maximum linear speed in m/s (e.g., `1.0`).

**2. `arduino.ino` (Arduino Code):**

* **Motor Pins (Lines 1-4):**
    * Verify `DIR1` (4), `PWM1` (5), `DIR2` (7), `PWM2` (6) match your Arduino to motor driver wiring.
* **Motor Control Logic (`setMotor` function & command parsing):**
    * The code assumes one motor might need its direction inverted (`int r_speed = r_dir == 0 ? -r_pwm : r_pwm;`). Adjust if your motors spin correctly or incorrectly with the default logic.

## 📋 Requirements

* **Hardware:** ESP32, Arduino (Uno/Nano, etc.), Motor Driver, 2x DC Motors (UGV chassis), Jumper Wires.
* **Software:** Arduino IDE, Blynk Account & App.
* **Libraries (ESP32):** `WiFi.h`, `BlynkSimpleEsp32.h` (Install via Arduino Library Manager).

## 🚀 Upload & Run

1.  **Blynk App:**
    * Create a project, get your Auth Token, Template ID & Name.
    * Add two **Slider** widgets:
        * One for **V0** (Linear Velocity, range e.g., -1.0 to 1.0 or as needed).
        * One for **V1** (Angular Velocity, range e.g., -1.0 to 1.0 or as needed).
2.  **Modify & Upload Code:**
    * Update `esp32.ino` and `arduino.ino` as per the "Code Configuration" section.
    * Upload `esp32.ino` to your ESP32.
    * Upload `arduino.ino` to your Arduino (remember to disconnect RX/TX if using Pins 0/1).
3.  **Connect & Power On:** Wire everything as per the "Wiring Guide".
4.  **Control:** Open the Blynk app and use the sliders to control the UGV.

---