/* Author: Jake O'Brien
  Date: 31/03/2021
  This code's purpose is to run a specific sequence of Binary numbers displayed as LEDs on the BAR LED all for specific
  amounts of time. */

#include <ee108.h>                                                                                          // include ee.108 library
int BarLEDs_SOLID(int, int, int);                                                                           // variables declared
int BarLEDs_BLINK(int, int, int, int);
int BarLEDs_PRINT(int);
int LED_ON_MS_BLINK1 = 50;
int LED_OFF_MS_BLINK1 = 250;
int LED_ON_MS_BLINK2 = 10;
int LED_OFF_MS_BLINK2 = 140;
const int BAUD_RATE = 9600;
int DURATION_BRIGHT = 300;
int unsigned ledStates;
int TOTAL_LOOPS_1 = 2;
int TOTAL_LOOPS_2 = 5;
const int END_OF_LOOP_BREAK_MS = 5000;

void setup() {
  Serial.begin(BAUD_RATE);                                                                                // the rate at which serial monitor runs
  for (int m = 0; m <= 9; m++)                                                                            // for loop to run through bar LED
    pinMode(3 + m, OUTPUT);
}

void loop() {
  int INTEGER_FOR_BINARY_1 = 3;                                                                           // decimal forms declared
  int INTEGER_FOR_BINARY_2 = 757;
  int INTEGER_FOR_BINARY_3 = 768;
  int INTEGER_FOR_BINARY_4 = random(1, 1023);

  BarLEDs_SOLID(INTEGER_FOR_BINARY_1, DURATION_BRIGHT);                                                   // functions called, with variables implemented in parameters
  BarLEDs_PRINT(INTEGER_FOR_BINARY_1);

  int DURATION_BRIGHT_DOUBLE = DURATION_BRIGHT * 2;                                                       // second function on and off time is double the first function time
  BarLEDs_SOLID(INTEGER_FOR_BINARY_2, DURATION_BRIGHT_DOUBLE);
  BarLEDs_PRINT(INTEGER_FOR_BINARY_2);

  BarLEDs_BLINK(INTEGER_FOR_BINARY_3, LED_ON_MS_BLINK1, LED_OFF_MS_BLINK1, TOTAL_LOOPS_1);
  BarLEDs_PRINT(INTEGER_FOR_BINARY_3);

  BarLEDs_BLINK(INTEGER_FOR_BINARY_4, LED_ON_MS_BLINK2, LED_OFF_MS_BLINK2, TOTAL_LOOPS_2);
  BarLEDs_PRINT(INTEGER_FOR_BINARY_4);
  delay(END_OF_LOOP_BREAK_MS);                                                                           // delay for end of loop
}

int BarLEDs_SOLID(int INTEGER_FOR_BINARY, int DURATION_BRIGHT) {                                         // function for first two solid flashes, with three parameters
  for (int BIT = 0; BIT <= 9; BIT++) {                                                                   // for BIT range of 10
    ledStates = bitRead(INTEGER_FOR_BINARY, BIT);                                                        // led states equals the bitRead of (the integer, incrementing BIT)
    if (ledStates == 1) {                                                                                // if ledState equals 1, light BAR up
      digitalWrite(BAR_LED_1_PIN + BIT, HIGH);
    }
    else {                                                                                               // otherwise, keep the off
      digitalWrite(BAR_LED_1_PIN + BIT, LOW);
    }
  }
  delay(DURATION_BRIGHT);                                                                                // delay on time by 300ms
  for (int i = 0; i <= 9; i++) {                                                                         // for the 9 BARs, keep the off (turns off)
    digitalWrite(BAR_LED_1_PIN + i, LOW);
  }
  delay(DURATION_BRIGHT);                                                                                // delay off time by 300 ms
  return ledStates;                                                                                      // return ledStates
}

int BarLEDs_BLINK(int INTEGER_FOR_BINARY, int LED_ON_MS_BLINK, int LED_OFF_MS_BLINK, int TOTAL_LOOPS) {  // function for two last blink flashes, with four parameters
  int s = 0;                                                                                             // s=0 declared
  while (s < TOTAL_LOOPS) {                                                                              // while s is less than parameter fro total amount of loops
    for (int BIT = 0; BIT <= 9; BIT++) {                                                                 // for BIT range of 10
      ledStates = bitRead(INTEGER_FOR_BINARY, BIT);                                                      // led states equals the bitRead of (the integer, incrementing BIT)
      if (ledStates == 1) {
        digitalWrite(BAR_LED_1_PIN + BIT, HIGH);
      }
      else {
        digitalWrite(BAR_LED_1_PIN + BIT, LOW);
      }
    }
    delay(LED_ON_MS_BLINK);                                                                              // delay by on time
    for (int i = 0; i <= 9; i++) {
      digitalWrite(BAR_LED_1_PIN + i, LOW);
    }
    delay(LED_OFF_MS_BLINK);                                                                             // delay by off time
    s++;                                                                                                 // incrementing by one each time
  }
  return ledStates;
}

int BarLEDs_PRINT(int INTEGER_FOR_BINARY) {                                                              // function for printing, with one parameter
  Serial.print("ledStates: ");                                                                           // print "ledStates: "
  for (int BIT = 9; BIT >= 0; BIT--) {
    ledStates = bitRead(INTEGER_FOR_BINARY, BIT);
    Serial.print(ledStates);                                                                             // print binary number
  }
  Serial.println(" ");                                                                                   // print gap in new line
  return 0;                                                                                              // return nothing
}
