#include <TFT_eSPI.h> // Library for display handling and font processing.

TFT_eSPI tft = TFT_eSPI(); // Creating a display object.

#define pinA 21 //Assigning GPIO inputs on the board for signals A and B.
#define pinB 22

volatile int position = 0; // Defining the angle variable.
volatile bool A_last = false, B_last = false; // Defining variables for the last state of each signal (for determining direction).

float lastDisplayedAngle = -999; // Variable for the last displayed angle on the screen.

void IRAM_ATTR encoderISR() {                    // Interrupt handler. Called every time one of the signals changes.
  bool A = digitalRead(pinA);                    // Reading the current value of the signals.
  bool B = digitalRead(pinB);

  if (A != A_last) {                             //If the signal has changed since the last time, we determine the direction of movement and update the variable state.
    if (A == B) position++;
    else position--;
    A_last = A;
  }

  if (B != B_last) {
    if (A != B) position++;
    else position--;
    B_last = B;
  }
}

void setup() {                                    //Startup settings.
  Serial.begin(115200);                           // Outputting debug data via the COM port.

  pinMode(27, OUTPUT); digitalWrite(27, HIGH);  // Display backlight.
  pinMode(pinA, INPUT_PULLUP);                   //Configuring the pins as inputs with pullup resistors.
  pinMode(pinB, INPUT_PULLUP);

  A_last = digitalRead(pinA);                    //Saving the initial states of the pins.
  B_last = digitalRead(pinB);

  attachInterrupt(digitalPinToInterrupt(pinA), encoderISR, CHANGE);         //Assigning interrupt handlers to both signals.
  attachInterrupt(digitalPinToInterrupt(pinB), encoderISR, CHANGE);

  tft.begin();                                                              //Initializing the screen.
  tft.setSwapBytes(false);                                                  //Parameter for using custom fonts.
  tft.setRotation(3);                                                       //Screen orientation, can be set to 0, 1, 2, or 3.
  tft.fillScreen(TFT_WHITE);                                                //Background color (the Chinese driver handles colors incorrectly; haven't figured it out yet).
  tft.setTextColor(TFT_NAVY, TFT_WHITE);                                    //Text color, text background color.
  tft.setFreeFont(&FreeSerifBold24pt7b);                                    //Font.

  // Начальная надпись
  tft.setCursor(20, 120);                                                  //Text position coordinates.
  tft.print("Angle: 0.0");                                                 //Start of the text.
  tft.print((char)247);                                                    //Degree symbol.
}

void loop() {                                                              //Starting the main loop.
  static int lastTouchState = 0;                                           //Flag indicating whether the screen was touched by a finger.
  uint16_t x, y;                                                           //Touch coordinates.

  if (tft.getTouch(&x, &y)) {                                              //Checking whether the user is touching the screen.
    if (!lastTouchState) {
      noInterrupts();                                                      //If a touch has started, disable interrupts and reset the counter to 0.
      position = 0;
      interrupts();
      lastDisplayedAngle = -999;

      // Clear the text area.
      tft.fillRect(0, 80, 320, 80, TFT_WHITE);

      tft.setCursor(20, 120);
      tft.print("Angle: 0.0");
      tft.print((char)247);
    }
    lastTouchState = 1;
  } else {
    lastTouchState = 0;
  }

  int pos_snapshot;
  noInterrupts();
  pos_snapshot = position;
  interrupts();

  float degrees = (float)pos_snapshot * 360.0 / 32000.0;           //Recalculate the position into degrees.

  if (abs(degrees - lastDisplayedAngle) > 0.1) {                   //Check if the angle has changed since the last time. If it has, update the text.
    lastDisplayedAngle = degrees;

    // Erase text only.
    tft.fillRect(0, 80, 320, 80, TFT_WHITE);

    tft.setCursor(20, 120);
   // tft.print("Angle: ");
    tft.print(degrees, 2);  // 1 decimal place.
    tft.print((char)247);   // Си
    
  }

  delay(30);                                                        //Screen refresh delay.

}
