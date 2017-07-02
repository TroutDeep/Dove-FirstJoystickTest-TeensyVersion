#include <Joystick.h>

/* Basic USB Joystick Example
   Arduino Leonardo becomes a USB joystick (adapted from Teensy example)

   NOTE-- Possibly not applicable for non-Teensy: You must select Joystick from the "Tools > USB Type" menu

   Pushbuttons should be connected to digital pins 0 and 1.
   Wire each button between the digital pin and ground.
   Potentiometers should be connected to analog inputs 0 to 1.

   This example code is in the public domain.
*/

// * Uncomment to enable debug output
// #define DEBUG_OUTPUT

// **NOTE**
// Board numbers referenced below are what's printed on my Leonardo clone
// Genuine Leonardo numbers may vary
// Pin numbers map to board numbers as shown below:

// PIN_D0 == 5
// PIN_D5 == 23
// PIN_D7 == 12
// PIN_D2 == 7
// PIN_D3 == 8

// First test... get it to build, then test program
// using correct pin mappings

// Digital pins
#define PIN_D0 2
#define PIN_D2 3
#define PIN_D3 4
#define PIN_D5 5
#define PIN_D7 6

// Analog pins
#define PIN_F4 A0
#define PIN_F5 A1

#define NUM_BUTTONS 5

int sampledVal, d0Val, d5Val, d7Val, d2Val, d3Val;
int i = 0;
int a0Val, a1Val;
int LEDState = 0;
const int ledPin = 11;

int buttonVal[NUM_BUTTONS];
int buttonPin[NUM_BUTTONS];

void setup() {

#ifdef DEBUG_OUTPUT  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Rebooted!\n");
#endif

// Initialize button pin assignments
  buttonPin[0] = PIN_D0;
  buttonPin[1] = PIN_D2;
  buttonPin[2] = PIN_D3;
  buttonPin[3] = PIN_D5;
  buttonPin[4] = PIN_D7;

// Initialize pin modes
  for(i=0; i < NUM_BUTTONS; i++)
  {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

// Read initial pin values
  for(i=0; i < NUM_BUTTONS; i++)
  {
    buttonVal[i] = digitalRead(buttonPin[i]);
  }

}

void loop() {
  
  LEDState = !LEDState;
  digitalWrite(ledPin, LEDState);

// Joystick X-Y axis

  a0Val = analogRead(PIN_F4);
  a1Val = analogRead(PIN_F5);
  
  Joystick.X(a0Val);
  Joystick.Y(a1Val);

// Loop through buttons, updating joystick if change

  for(i=0; i < NUM_BUTTONS; i++)
  {
    sampledVal = digitalRead(buttonPin[i]);
    if (sampledVal != buttonVal[i])
    {
#ifdef DEBUG_OUTPUT
      Serial.print("sampledVal == ");
      Serial.print(sampledVal);
      Serial.print(" buttonVal == ");
      Serial.print(buttonVal[i] + 1);
      Serial.print(" button == ");
      Serial.print(i);
      Serial.print(" pressed!\n");
#endif
      buttonVal[i] = sampledVal;
      Joystick.button(i+1, !buttonVal[i]);  // Update button; buttons start at 1, not 0; active low, so invert
    }
  }

  // Delay 50 ms == 20 Hz
  delay(50);


#ifdef DEBUG_OUTPUT
  Serial.print("Analog stick = [");
  Serial.print(a0Val);
  Serial.print(",");
  Serial.print(a1Val);
  Serial.print("]\n");

  for(i=0; i < NUM_BUTTONS; i++)
  {
    Serial.print(buttonVal[i]);
    Serial.print("\n");
  }
#endif
}

