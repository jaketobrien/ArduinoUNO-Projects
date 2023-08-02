/*Author: Jake O'Brien
  Date: 24/05/2021
  This code's purpose is to run a specific sequence of Binary numbers displayed as LEDs on the BAR LED all for specific
  amounts of time. */

#include <ee108.h>

int BarLEDs_SOLID(int, int);
int BarLEDs_BLINK(int);
int BarLEDs_RANDOM(int);
const int BUTTON_POLL_MS = 50;                                                   // constants used in the code
const int BETWEEN_REPS_MS = 500;
int unsigned LED_ON_MS;
int unsigned LED_OFF_MS;
const int BAUD = 9600;
int unsigned ledStates;

void setup() {
  Serial.begin(BAUD);                                                            // the rate at which serial monitor runs
  for (int m = 0; m <= 9; m++)                                                   // for loop to run through bar LED
    pinMode(3 + m, OUTPUT);
}

void loop() {
  int sw1Event;                                                                  // used when checking SW1
  int sw2Event;                                                                  // user when checking SW2
  int a = 3;                                                                         // int a decalared
  int b = 245;
  int c = 768;
  int d = random(1023);
  int unsigned ledStates1;
  int unsigned ledStates2;
  int PIN = 3;                                                                   // starting PIN declared at 3
  int BIT = 0;
  int s = 0;

  while (s < 1) {
    int BarLEDs_SOLID( ledStates1, ledStates2);
    Serial.print("ledState: ");
    Serial.print("%d", ledStates1);
    Serial.println("ledState: ");
    Serial.print("%d", ledStates2);
    int BarLEDs_BLINK(int);
    int BarLEDs_RANDOM(int);
    s++;
  }
}

int BarLEDs_SOLID(int, int) {
  int unsigned ledStates1;
  int unsigned ledStates2;
  LED_ON_MS = 300;
  LED_OFF_MS = 300;
  int s = 0;
  int a = 3;                                                                         // int a decalared
  int b = 245;
  while (s <= 1) {
    if (s == 0) {
      for (BIT; BIT <= 10; BIT++) {                                                // for BIT range of 10
        ledStates1 = bitRead(a, BIT);
      }
      if (ledStates1 == 1) {
        digitalWrite(BAR_LED);
        delay(LED_ON_MS);
      }
      else {
        digitalWrite(BAR_LED);
        delay(LED_OFF_MS);
      }
      s++
    }
    LED_ON_MS = LED_ON_MS * 2;
    LED_OFF_MS = LED_OFF_MS * 2;
    if (s == 1) {
      for (BIT; BIT <= 10; BIT++) {                                                // for BIT range of 10
        ledStates2 = bitRead(b, BIT);
      }
      if (ledStates2 == 1) {
        digitalWrite(BAR_LED, HIGH);
        delay(LED_ON_MS);
      }
      else {
        digitalWrite(BAR_LED, LOW);
        delay(LED_OFF_MS);
      }
      s++
    }
  }
  return ledStates1;
  return ledStates2;
}

int BarLEDs_BLINK(int) {
  int unsigned ledStates;
  LED_ON_MS = 50;
  LED_OFF_MS = 250;
  int s = 0;
  int c = 768;
  while (s < 2) {
    for (BIT; BIT <= 10; BIT++) {                                                // for BIT range of 10
      ledStates = bitRead(c, BIT);
      if (ledStates == 1) {
        digitalWrite(BAR_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(LED_ON_MS);                       // wait for time stated
      }
      else {
        digitalWrite(BAR_LED, LOW);    // turn the LED off by making the voltage LOW
        delay(LED_OFF_MS);
      }
    }
    s++
  }
}

int BarLEDs_RANDOM(int) {

}
