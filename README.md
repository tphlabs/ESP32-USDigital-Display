# ESP32-USDigital-Display
Arduino sketch for ESP32 that reads a US Digital encoder, calculates angle, and shows it on a TFT display with touch reset support.


Requirements

- ESP32 development board (e.g. WROOM or S3)
- Rotary encoder (e.g. US Digital EM2)
- USB cable for ESP32
- Arduino IDE installed
- Internet connection

Step-by-step instructions

1. Install Arduino IDE

  Download and install Arduino IDE from the official website:  
  [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)



2. Install ESP32 board support

  2.1. Open Arduino IDE.
  2.2. Go to `File > Preferences`.
  2.3. In the field **Additional Boards Manager URLs**, add:

  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

  2.4. Click **OK**.
  2.5. Go to `Tools > Board > Boards Manager`.
  2.6. Search for **ESP32 Dev Module** and install the latest version.



3. Install required libraries

  3.1. Go to `Tools > Manage Libraries...`
  3.2. Search for **TFT_eSPI**
  3.3. Click **Install**


4. Configure TFT_eSPI

  The TFT_eSPI library needs a configuration file with display settings.

  4.1. Locate the TFT_eSPI library folder on your computer:
  - Usually: `Documents/Arduino/libraries/TFT_eSPI/`
  4.2. Replace the file `User_Setup.h` in that folder with the one provided in this project.
  This file defines screen settings and pin connections.
  If you have other projects using TFT_eSPI, back up your original `User_Setup.h`.


5. Open and upload the sketch

  5.1. Open `sketch_display_count_circle.ino` in Arduino IDE.
  5.2. Go to `Tools > Board` and select your ESP32 board (e.g., **ESP32 Dev Module**).
  5.3. Go to `Tools > Port` and choose the correct COM port (appears when ESP32 is connected).
  5.4. Click the **Upload** button to compile and upload the sketch.


How it works

- The encoder is connected to:
- `GPIO 21` → Signal A  
- `GPIO 22` → Signal B  
- The TFT screen shows the current angle in degrees.
- Touching the screen resets the angle to zero.


File List

- `sketch_display_count_circle.ino` — main sketch
- `User_Setup.h` — TFT screen configuration (must be placed inside the TFT_eSPI library)


Notes

- Serial Monitor output is available at 115200 baud (for debugging).
- The angle is updated on screen only when it changes.
- Screen refresh is limited to avoid flickering.


Resetting angle

Touch the screen with a finger to reset the angle to **0.0°**.
