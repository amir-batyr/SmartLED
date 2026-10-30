# Arduino IoT Cloud RGB Light Controller

An IoT project that allows remote control of an RGB LED using the **Arduino IoT Cloud**. The system listens for color and state changes from the cloud dashboard and drives an inverted/common-anode RGB LED via PWM signal pins.

---

## 🛠️ Hardware Requirements

- **Microcontroller:** ESP32, ESP8266, or any Arduino IoT Cloud-compatible board with PWM outputs.
- **IKEA RGB LED STRIP 1M:**
- **Connecting Wires**

---

## 🔌 Pin Mapping

Based on the default sketch configuration:

| RGB Channel | Microcontroller Pin | 
| :--- | :--- | 
| **Red (R)** | `Pin 18` |
| **Blue (B)** | `Pin 19` |
| **Green (G)** | `Pin 21` |

> **Note:** The code uses `255 - brightness` active-low logic for driving common anode LEDs. If using common cathode, adjust the `analogWrite` formulas accordingly.

---

## 📁 File Structure

```text
.
├── main.ino            # Main sketch code (setup, loop, and cloud callbacks)
├── thingProperties.h   # IoT Cloud properties, variables, and network configurations
└── arduino_secrets.h   # Sensitive network credentials (SSID & Password)
```

---

## 🚀 Setup & Installation

### 1. Arduino IoT Cloud Configuration
1. Go to [Arduino IoT Cloud](https://app.arduino.cc/).
2. Create a new **Thing**.
3. Add a Cloud Variable named `light` with the **Colored Light** property type.
4. Configure network details (Wi-Fi SSID and Password).

### 2. Code Setup
1. Copy the provided `.ino` sketch into your main file.
2. Ensure `thingProperties.h` and `arduino_secrets.h` are correctly generated and configured in your project directory.
3. Define your Wi-Fi credentials in `arduino_secrets.h`:
   ```cpp
   #define SECRET_SSID "Your_WiFi_SSID"
   #define SECRET_OPTIONAL_PASS "Your_WiFi_Password"
   ```

### 3. Upload & Run
1. Connect your micro-controller board via USB.
2. Select your board and port in the Arduino IDE or Cloud Editor.
3. Compile and upload the code.
4. Open the **Serial Monitor** (set to 9600 or 115200 baud) to view network and Cloud connection status updates.

---

## 💻 How It Works

- **`setup()`**: Initializes cloud connection settings, configures debug messaging level to `2`, and sets output modes for pins 18, 19, and 21.
- **`loop()`**: Calls `ArduinoCloud.update()` continuously to maintain communication and keep property states synchronized.
- **`onLightChange()`**: Triggered whenever the `light` variable changes on the dashboard:
  - When the switch is **ON**, it extracts $R, G, B$ values ($0-255$) and writes inverted PWM signals (`255 - color`) to the output pins.
  - When the switch is **OFF**, it sets all pins to full high (`255`), effectively turning off the common anode LED.