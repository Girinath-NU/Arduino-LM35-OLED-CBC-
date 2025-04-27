# ESP32 LM35 Temperature Monitor with OLED Display and Buzzer Alert

This project reads temperature values from an **LM35 sensor** using an **ESP32**, displays the temperature on an **OLED screen**, and sounds a **buzzer** if the temperature exceeds a threshold (26°C).  
It also connects to Wi-Fi for future upgrades (e.g., IoT integration).

---

## Components Required
- ESP32 Development Board
- LM35 Temperature Sensor
- SSD1306 OLED Display (128x64, I2C)
- Buzzer
- Jumper wires
- Breadboard

---

## Wiring Diagram

| Component | ESP32 Pin Connection |
|:---------:|:--------------------:|
| LM35 Vout | GPIO34 (Analog Input) |
| LM35 Vcc  | 3.3V                  |
| LM35 GND  | GND                   |
| OLED SDA  | GPIO21                |
| OLED SCL  | GPIO22                |
| OLED VCC  | 3.3V                  |
| OLED GND  | GND                   |
| Buzzer +  | GPIO27                |
| Buzzer -  | GND                   |

---

### LM35 Pinout

```
(Front view, flat side facing you)
   
    +--------+
    |        |
    | LM35   |
    |        |
    +--------+
     | | |
     | | |
     | | +-- Vout (middle pin) -> ESP32 GPIO34
     | +---- GND (left pin) -> ESP32 GND
     +------ VCC (right pin) -> ESP32 3.3V
```

**Important:**  
- LM35 works between 4V–30V typically, but with ESP32 (3.3V logic), powering it with **3.3V** is safer.  
- Connect the **middle pin (Vout)** to the ESP32 **analog input pin** (GPIO34).

---

## How It Works

1. ESP32 reads analog voltage from the LM35 sensor.
2. Converts voltage to Celsius temperature (10 mV/°C).
3. Displays the temperature on the OLED display.
4. If temperature > 26°C:
   - Displays a warning message on OLED.
   - Activates the buzzer for an alert.
5. If temperature <= 26°C:
   - The buzzer remains off.
6. ESP32 connects to Wi-Fi at startup (currently unused but ready for expansion like IoT updates).

---

## Code Overview

- **Libraries Used**:
  - `Wire.h` — For I2C communication.
  - `Adafruit_GFX.h` — Core graphics library for OLED.
  - `Adafruit_SSD1306.h` — OLED driver.
  - `WiFi.h` — To connect ESP32 to Wi-Fi.

- **Key Macros**:
  - `LM35_PIN = 34`
  - `BUZZER_PIN = 27`
  - OLED on I2C (`Wire.begin(21, 22)`)

---

## Future Improvements
- Push temperature data to a web server.
- Control thresholds via a mobile app.
- Log temperature values over time (data logging).

---

## Notes
- Make sure your OLED display address is **0x3C**. Otherwise, change it in the code.
- If the LM35 gives unstable readings, add a **0.1 µF capacitor** between Vout and GND.


