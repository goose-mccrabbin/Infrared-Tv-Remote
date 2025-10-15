#include <Arduino.h>

#if !defined(ARDUINO_ESP32C3_DEV) 
// Disable static receiver code for RISC-V compiler bug.
// Saves program memory and RAM if receiving functions are not required.
#define DISABLE_CODE_FOR_RECEIVER
#endif

//Both of these are included in the arduino IDE libraries
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp> // IR library

//These will change depending on the microcontroller
// Button pin definitions
const int powerButton  = 4;
const int middleButton = 6;
const int upButton     = 5;
const int downButton   = 8;
const int rightButton  = 7;
const int leftButton   = 3;
const int inputButton  = 2;

// LED pin definitions
const int led0 = 0;
const int led1 = 1;

// Button state variables
int powerState, inputState, upState, downState, leftState, rightState, middleState;

// IR command codes
// These codes will change per TV remote, they can be found by looking up your TV remote ir codes or using an IR reciever decoder.
uint8_t sRepeats = 0;
uint8_t Middle = 0x44;
uint8_t Power  = 0x08;
uint8_t Up     = 0x45;
uint8_t Down   = 0x46;
uint8_t Left   = 0x47;
uint8_t Right  = 0x48;
uint8_t Input  = 0x2F;
uint8_t VolUp  = 0x02;
uint8_t VolDown= 0x03;
uint8_t Back   = 0x4A;
uint8_t Exit   = 0x49;

void setup() {
    // Initialize LEDs
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);

    // Initialize buttons as input with pull-ups
    pinMode(powerButton, INPUT_PULLUP);
    pinMode(middleButton, INPUT_PULLUP);
    pinMode(upButton, INPUT_PULLUP);
    pinMode(downButton, INPUT_PULLUP);
    pinMode(rightButton, INPUT_PULLUP);
    pinMode(leftButton, INPUT_PULLUP);
    pinMode(inputButton, INPUT_PULLUP);

    // Initialize Serial Monitor
    Serial.begin(9600);

    // Initialize IR sender
    IrSender.begin(); 
    disableLEDFeedback(); // optional LED feedback from library
}

void loop() {
    digitalWrite(led1, HIGH); // always-on LED indicator

    // Read button states
    powerState  = digitalRead(powerButton);
    inputState  = digitalRead(inputButton);
    upState     = digitalRead(upButton);
    downState   = digitalRead(downButton);
    leftState   = digitalRead(leftButton);
    rightState  = digitalRead(rightButton);
    middleState = digitalRead(middleButton);

    // Handle each button press
    if (powerState == LOW) {
        Serial.println("Power");
        IrSender.sendNECRaw(0x20DF23DC); // raw NEC code
        blinkLED(led0);
    }

    if (inputState == LOW) {
        Serial.println("Input");
        IrSender.sendNEC(0x04, Input, sRepeats);
        blinkLED(led0);
    }

    if (upState == LOW) {
        Serial.println("Up");
        IrSender.sendNEC(0x04, Up, sRepeats);
        blinkLED(led0);
    }

    if (downState == LOW) {
        Serial.println("Down");
        IrSender.sendNEC(0x04, Down, sRepeats);
        blinkLED(led0);
    }

    if (leftState == LOW) {
        Serial.println("Left");
        IrSender.sendNEC(0x04, Left, sRepeats);
        blinkLED(led0);
    }

    if (rightState == LOW) {
        Serial.println("Right");
        IrSender.sendNEC(0x04, Right, sRepeats);
        blinkLED(led0);
    }

    if (middleState == LOW) {
        Serial.println("Middle");
        IrSender.sendNEC(0x04, Middle, sRepeats);
        blinkLED(led0);
    }

    delay(100); // debounce & prevent repeated signals
}

// Helper function to blink an LED briefly
void blinkLED(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
}
