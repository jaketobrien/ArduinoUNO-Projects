/* Author: Jake O'Brien
   Date: 12/05/21
   This code's purpose is to take an input of letters and non-alphabetic entities and put only the directional letters from the input into a buffer
   with a max length of 10. The resultant hould then be calculated and printed, along with the hand-side it is pointing, the slope and compass direction.
*/

#include <ee108.h>

//------------------------------------------------------------
// types
//------------------------------------------------------------

struct Vector2d {                                                                                          // a structure to represent a 2d vector point in cartesian coordinates
  int x;
  int y;
};

typedef  struct  Vector2d;                                                                                // a typedef declared as a structure called Vector2d

//------------------------------------------------------------
// constants
//------------------------------------------------------------

const int BAUD_RATE = 9600;                                                                                // BAUD RATE declared as 9600 ms

#define BUF_STRLEN 9                                                                                       // size of buffer for accepting input characters

//------------------------------------------------------------
// function declarations/prototypes
//------------------------------------------------------------

void printLetterBuffer(char *BUFFER_ARRAY, int BUFFER_LENGTH);                                             // function to print buffer conataining letters, @ params: pointer buffer string that holds letters, buffer length set
int addToFifoBuffer(char *BUFFER_ARRAY, int BUFFER_LENGTH, char LETTER);                                   // function to add letter to buffer, @ params: pointer buffer string that holds letters, buffer length set, letter that was inputted
void resultantVector(char *BUFFER_ARRAY, int BUFFER_LENGTH, Vector2d *ResultantVector);                    // function to calculate the resultant vector, @ params: pointer buffer string that holds letters, buffer length set, struct Vector2d with pointer for variable of resultant vector
void SideOfVector(int POINT_VAR_X);                                                                        // function to tell what side the vector is pointing, @ param: 'x' coordinate
int calcSlope(Vector2d *ResultantVector);                                                                  // function to calculate the slope, @ param: struct Vector2d with pointer for variable of resultant vector
void compassDirection(int SLOPE, int POINT_VAR1, int POINT_VAR2);                                          // function to calculate the compass direction, @ params: the calculated slope, 'x' coordinate and 'y' coordinate
//void compassDirection(int POINT_VAR1, int POINT_VAR2);                                                   // alternative version of function compass direction

//------------------------------------------------------------
// top level functions
//------------------------------------------------------------

void setup() {
  Serial.begin(BAUD_RATE);                                                                                 // serial set up
  Serial.println("\n\nA4_ExampleSerialEchoNoBuffer starting.");
  Serial.println("[Ensure that you have line ending to newline on console window]\n");
}

void loop() {
  static Vector2d ResultantVector;                                                                         // static struct variable called ResultantVector declared
  char BufferString[BUF_STRLEN] = {};                                                                      // Buffer string declared with its length and set equal to an empty string
  static int BufferStringLength = 0;                                                                       // static string length decalred and set equal to zero
  Serial.println("Type characters and hit return - only alphabetic characters will be echoed:");           // print info to serial monitor
  Serial.print("\n\tReceived: ");

  while (true) {                                                                                           // we don't limit the number of characters read in here, so there is no condition to evaluate here
    char c;

    while (Serial.available() == 0)                                                                        // wait until at least one character has been entered
      continue;

    c = Serial.read();                                                                                     // we now have at least 1 character, read 1 character

    if ((c == '\n') || (c == '\r') || (c ==  isspace(c))) {                                                // a newline or space indicates the end of the word, so it will break out to process it
      break;
    }

    if (!isalpha(c))                                                                                       // ignore any characters that are not alphabetic
      Serial.print('.');
    else
      Serial.print(c);                                                                                     // print letter

    if (isupper(c)) {                                                                                      // if letter is upper-case change it to lower case
      c = tolower(c);
    }
    if (c == 'j' || c == 'k' || c == 'l' || c == 'i') {                                                    // if letter is equal to a directional letter
      BufferStringLength++;                                                                                // increase the buffer length
      addToFifoBuffer(BufferString, BUF_STRLEN, c);                                                        // add to fifo buffer
    }
  }
  printLetterBuffer(BufferString, BufferStringLength);                                                     // print new buffer with directional letters
  resultantVector(BufferString, BufferStringLength, &ResultantVector);                                     // calculate the resultant vector
  Serial.print("\n\tResultant: x = ");                                                                     // print info and 'x' coordinate of resultant vector in monitor
  Serial.print(ResultantVector.x);
  Serial.print(", y = ");                                                                                  // print info and 'y' coordinate of resultant vector in monitor
  Serial.print(ResultantVector.y);
  SideOfVector(ResultantVector.x);                                                                         // calculate the side the vector is pointing and print to monitor
  calcSlope(&ResultantVector);                                                                             // calculate slope and print to monitor
  compassDirection(calcSlope, ResultantVector.x, ResultantVector.y);                                       // calculate compass direction and print to monitor

  Serial.println("\n");                                                                                    // once we get here, we encountered a newline or space and broke out
  // of the loop. Display a newline and then we're ready to do it all again
}

/**
   Function that prints the current password

   @param *BUFFER_ARRAY   pointer that points to the character array
   @param BUFFER_LENGTH   max length of buffer to be passed through
*/

void printLetterBuffer(char *BUFFER_ARRAY, int BUFFER_LENGTH) {
  Serial.print("\n\tBuffer contents: ");                                                                  // print info to monitor
  int i = 0;                                                                                              // iterator decalred at zero
  for (i; i < BUFFER_LENGTH; i++) {                                                                       // for i iterating through buffer length
    Serial.print(*(BUFFER_ARRAY + i));                                                                    // print the pointed position + the iteration number
  }
  *(BUFFER_ARRAY + BUFFER_LENGTH + 1) = '\0';                                                             // string terminator at end of string
}

/**
   Function that adds letter to fifo buffer

   @param  *BUFFER_ARRAY   pointer that points to the character array
   @param  BUFFER_LENGTH   max length of buffer to be passed through
   @param  LETTER          letter that is now been iterated on
*/


int addToFifoBuffer(char *BUFFER_ARRAY, int BUFFER_LENGTH, char LETTER) {
  for (BUFFER_LENGTH; BUFFER_LENGTH > 0; BUFFER_LENGTH--) {                                               // for i <= length of fifo, fifo buffer with the index of the fifo length - i is equal to the previous index
    *(BUFFER_ARRAY + BUFFER_LENGTH) = *(BUFFER_ARRAY + BUFFER_LENGTH - 1);
  }
  *BUFFER_ARRAY = LETTER;                                                                                 // this position is the position that the letter takes
}

/**
   Function that calculates the resultant vector

   @param  *BUFFER_ARRAY              pointer that points to the character array
   @param  BUFFER_LENGTH              max length of buffer to be passed through
   @param  Vector2d *ResultantVector  struct Vector2d with pointer for variable of resultant vector
*/

void resultantVector(char *BUFFER_ARRAY, int BUFFER_LENGTH, Vector2d *ResultantVector) {
  int i = 0;                                                                                            // iterator called i decalred and set to 0
  static Vector2d Point_j = { -1, 0};                                                                   // static variable struct names with values
  static Vector2d Point_k = {0, -1};
  static Vector2d Point_l = {1, 0};
  static Vector2d Point_i = {0, 1};

  int sum_x = 0;                                                                                        // sum of x and y declared and set to 0
  int sum_y = 0;

  for (i; i < BUFFER_LENGTH; i++) {                                                                     // for iterating through buffer length, if index iterated on equals letter, sum_var = point of letter value + sum_var. Same for all for loops
    if (*(BUFFER_ARRAY + i) == 'j') {
      sum_x = Point_j.x + sum_x;
      sum_y = Point_j.y + sum_y;
    }
    if (*(BUFFER_ARRAY + i) == 'k') {
      sum_x = Point_k.x + sum_x;
      sum_y = Point_k.y + sum_y;
    }
    if (*(BUFFER_ARRAY + i) == 'l') {
      sum_x = Point_l.x + sum_x;
      sum_y = Point_l.y + sum_y;
    }
    if (*(BUFFER_ARRAY + i) == 'i') {
      sum_x = Point_i.x + sum_x;
      sum_y = Point_i.y + sum_y;
    }
  }
  ResultantVector->x = sum_x;                                                                         // resultant vector is pointed at var coordinate and is set equal to the sum of var
  ResultantVector->y = sum_y;

}

/**
   Function that calculates and prints the slope

   @param  Vector2d *ResultantVector  struct Vector2d with pointer for variable of resultant vector
*/

int calcSlope(Vector2d *ResultantVector) {
  int SLOPE;                                                                                          // int SLOPE declared
  int coord_x = ResultantVector->x;                                                                   // coord x decalred and set equal to resultant vector pointing at x
  int coord_y = ResultantVector->y * 1000;                                                            // coord y decalred and set equal to resultant vector pointing at y multiplied by 1000

  if (coord_x == 0) {                                                                                 // if x = 0, set slope to 99999 instead of infinty and print slope
    SLOPE = 99999;
    Serial.print(SLOPE);
  }
  else {                                                                                              // else: slope is y/x and print it
    SLOPE = coord_y / coord_x;
    Serial.print("1000*Slope = ");
    Serial.print(SLOPE);
  }
  return SLOPE;                                                                                       // return slope
}

/**
   Function that calculates the side that the vector is pointing

   @param  POINT_VAR_X  x coordinate
*/

void SideOfVector(int POINT_VAR_X) {
  Serial.print("\n\tDirection: ");                                                                    // print info to monitor
  if (POINT_VAR_X > 0) {                                                                              // if x > 0, its on RHS and vice versa for LHS, if x = 0, its on y axis
    Serial.print("RHS, ");
  } if (POINT_VAR_X < 0) {
    Serial.print("LHS, ");
  }
  if (POINT_VAR_X == 0) {
    Serial.print("On the y-axis, ");
  }
}

/**
   Function that calculates and prints compass direction

   @param  SLOPE        calculated slope
   @param  POINT_VAR1   x coordinate
   @param  POINT_VAR2   y coordinate
*/

void compassDirection(int SLOPE, int POINT_VAR1, int POINT_VAR2) {

  Serial.print(", Compass Direction: ");                                                              // print info to monitor

  if (SLOPE > 0 && POINT_VAR1 > 0) {                                                                  // if statemnts using the slopes approx value in conjunction with one varibales approx value to get an approx direction
    Serial.print("North-East");
  }
  if (SLOPE > 0 && POINT_VAR1 < 0) {
    Serial.print("South-West");
  }
  if (SLOPE < 0 && POINT_VAR1 > 0) {
    Serial.print("South-East");
  }
  if (SLOPE < 0 && POINT_VAR1 < 0) {
    Serial.print("North-West");
  }
  if (SLOPE == 0 && POINT_VAR1 > 0) {
    Serial.print("East");
  }
  if (SLOPE == 0 && POINT_VAR1 < 0) {
    Serial.print("West");
  }
  if (SLOPE == 0 && POINT_VAR2 > 0) {
    Serial.print("North");
  }
  if (SLOPE == 0 && POINT_VAR1 < 0) {
    Serial.print("South");
  }
}

/**
   Alternative function that calculates and prints compass direction

   @param  POINT_VAR1   x coordinate
   @param  POINT_VAR2   y coordinate
*/

//void compassDirection(int POINT_VAR1, int POINT_VAR2) {
//
//  Serial.print(", Compass Direction: ");
//
//  if (POINT_VAR1 && POINT_VAR2 == 0) {                                                                     // if statemnts using two varibale's approx value to get an approx direction
//    Serial.print("Origin");
//  }
//  if (POINT_VAR1 > 0 && POINT_VAR2 == 0) {
//    Serial.print("North");
//  }
//  if (POINT_VAR1 >= 1 && POINT_VAR2 >= 1) {
//    Serial.print("North East");
//  }
//  if (POINT_VAR1 >= 1 && POINT_VAR2 == 0) {
//    Serial.print("East");
//  }
//  if (POINT_VAR1 >= 1 && POINT_VAR2 <= -1) {
//    Serial.print("South East");
//  }
//  if (POINT_VAR1 == 0 && POINT_VAR2 <= -1) {
//    Serial.print("South");
//  }
//  if (POINT_VAR1 <= -1 && POINT_VAR2 <= -1) {
//    Serial.print("South West");
//  }
//  if (POINT_VAR1 == 0 && POINT_VAR2 <= -1) {
//    Serial.print("West");
//  }
//  if (POINT_VAR1 <= -1 && POINT_VAR2 >= 1) {
//    Serial.print("North West");
//  }
//}
