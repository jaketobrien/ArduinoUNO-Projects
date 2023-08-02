/* Author: Jake O'Brien
  Date: 14/04/2021
  This code's purpose is to randomly pick a HEX number from the HEX table and display it to the seven segment display. It will
  also print the decimal, binary and HEX to the serila monitor*/

#include <ee108.h>                                                                                          // include ee.108 library

#define NUMBER_OF_CODES 16                                                                                  // number of codes defiines as 16
#define SEG_DP_PIN 12                                                                                       // pins defined as numbers
#define SEG_A_PIN 11
#define SEG_B_PIN 10
#define SEG_C_PIN 9
#define SEG_D_PIN 8
#define SEG_E_PIN 7
#define SEG_F_PIN 6
#define SEG_G_PIN 5
//int decimal_point = SEG_DP_PIN;                                                                           // int name for SSD pins for alternative solution                                                    
//int a = SEG_A_PIN;
//int b = SEG_B_PIN;
//int c = SEG_C_PIN;
//int d = SEG_D_PIN;
//int e = SEG_E_PIN;
//int f = SEG_F_PIN;
//int g = SEG_G_PIN;
int const DURATION_ON_MS = 2000;                                                                            // int constant of duration

byte lookupHexCode(byte);                                                                                   // HEX lookip table function declared
void SevenSegmentDisplay(byte);                                                                             // SSD loop function declared
//void SevenSegmentDisplayOff();                                                                            // function option to turn off for a certain period of time
int SevenSegmentsPrint(int);                                                                                // function prints decimal, binary and HEX to serial monitor

int BAUD_RATE_MS = 9600;                                                                                    // BAUD RATE set at 9600 ms
int const SUPERLOOP_MS = 3000;                                                                              // time until loop runs again

void setup() {
  Serial.begin(BAUD_RATE_MS);                                                                               // print to serial monitor
  Serial.println("========= HexCodeToSevenSegment starting ============");

  for (int s=0; s>=7; s--){                                                                                 // for loop to initiate pins
    pinMode(SEG_DP_PIN - s, OUTPUT);
  }

//  pinMode(SEG_DP_PIN, OUTPUT); //Decimal Point
//  pinMode(SEG_A_PIN, OUTPUT);  //A
//  pinMode(SEG_B_PIN, OUTPUT);  //B
//  pinMode(SEG_C_PIN, OUTPUT);  //C
//  pinMode(SEG_D_PIN, OUTPUT);  //D
//  pinMode(SEG_E_PIN, OUTPUT);  //E
//  pinMode(SEG_F_PIN, OUTPUT);  //F
//  pinMode(SEG_G_PIN, OUTPUT);  //G
}

void loop() {
  int RANDOM_VALUE = random(NUMBER_OF_CODES);                                                                 // variable for random num in range of 0 to 16

  lookupHexCode(RANDOM_VALUE);                                                                                // HEX code table function beinf called with parameter as random value
  SevenSegmentsPrint(RANDOM_VALUE);                                                                           // function to print to serial monitor with random value as parameter
  delay(DURATION_ON_MS);                                                                                      // delay of time to stay on
  //void SevenSegmentDisplayOff();                                                                            // function option to turn off for a certain period of time

  delay(SUPERLOOP_MS);                                                                                        // delay of time for loop to restart

}

byte lookupHexCode(byte RAND_NUM) {                                                                           // function start with parameter
   static const byte TABLE_FOR_HEX[NUMBER_OF_CODES] = {                                                       // array of table of HEX with the length/indexes of the number of codes
    0x7E, 0x30, 0x6D, 0x79,
    0x33, 0x5B, 0x5F, 0x70,
    0x7F, 0x73, 0x77, 0x1F,
    0x4E, 0x3D, 0x4F, 0x47
  };
  SevenSegmentDisplay(TABLE_FOR_HEX[RAND_NUM]);                                                               // now runs the SSD loop with the parameter as the table of HEX
}

void SevenSegmentDisplay(byte FUNCTION_TABLE_FOR_HEX){                                                        // void becomes nothing is being returned, SSD loop function
  for (int BIT = 0; BIT < 8; BIT++){                                                                          // for each BIT (from least most significant) iterate through binary number
          int SSD_States = bitRead(FUNCTION_TABLE_FOR_HEX, BIT);                                              // SSD states equals the bitRead of (table of HEX, incrementing BIT)
      if (SSD_States == 1) {                                                                                  // if BIT equals 1, light up segment
        digitalWrite(SEG_G_PIN + BIT, HIGH);
      }
      else {
        digitalWrite(SEG_G_PIN + BIT, LOW);                                                                   // else, keep segment low
      }
  }
}

//  static const byte TABLE_FOR_HEX[NUMBER_OF_CODES] = {                                                      // alternative method using if statements
//    0x0, 0x1, 0x2, 0x3,
//    0x4, 0x5, 0x6, 0x7,
//    0x8, 0x9, 0xA, 0xB,
//    0xC, 0xD, 0xE, 0xF
//  }
//  
//  if(NUM !=1 && NUM != 4 && NUM != 11 && NUM != 13){
// digitalWrite(a, HIGH);
//  }
// 
// if(NUM != 5 && NUM != 6 && NUM != 11 && NUM != 12 && NUM != 14 && NUM != 15){
// digitalWrite(b, HIGH);
// }
// 
// if(NUM !=2 && NUM != 12 && NUM != 14 && NUM != 15){
// digitalWrite(c, HIGH);
// }
// 
// if(NUM != 1 && NUM != 4 && NUM != 7 && NUM != 10 && NUM != 15){
// digitalWrite(d, HIGH);
// }
// 
// if(NUM == 2 || NUM ==6 || NUM == 8 || NUM == 0 || NUM == 10 || NUM == 11 || NUM == 12 || NUM == 13 || NUM == 14 || NUM == 15){
// digitalWrite(e, HIGH);
// }
// 
// if(NUM != 1 && NUM !=2 && NUM !=3 && NUM !=7 && NUM != 13){
// digitalWrite(f,HIGH);
// }
// 
// if (NUM !=0 && NUM !=1 && NUM !=7 && NUM != 12){
// digitalWrite(g, HIGH);
// }

//void SevenSegmentDisplayOff(){                                                                               // optional function to turn off SSD immediately after on time

  
//  digitalWrite(a,LOW);
//  digitalWrite(b,LOW);
//  digitalWrite(c,LOW);
//  digitalWrite(d,LOW);
//  digitalWrite(e,LOW);
//  digitalWrite(f,LOW);
//  digitalWrite(g,LOW);
//}

int SevenSegmentsPrint(int RAND_NUM){                                                                         // function to print decimal, binary and HEX numbers to serial monitor
  Serial.print("For number "); 
  Serial.print(RAND_NUM);
  Serial.print(", binary = ");
  for (int BIT = 3; BIT >= 0; BIT--){                                                                         // Binary number of the decimal and HEX number, iterates through 4 BITs
  int BINARY_RANDOM_VALUE = bitRead(RAND_NUM, BIT); 
  Serial.print(BINARY_RANDOM_VALUE);
  }
  Serial.print(", HEX code = ");
  Serial.println(RAND_NUM, HEX);
}
