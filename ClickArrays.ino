/*  Author: Jake O'Brien
    Date: 28/04/21
    This code's purpose is to start off with a set number of arrays and allow the user to change the arrays, through
    the length/amount of time the switch has been clicked
*/

#include <ee108.h>                                                                                                      // including ee108 library

#define ARRAY_LEN 10                                                                                                    //defining the array length

const int BAUD_RATE = 9600;                                                                                             // Baud Rate set
const int SUPERLOOP_DELAY_MS = 50;                                                                                      // delay between loops

void randomizeArray(int *array, int len, int minVal, int maxVal);                                                       // Function to radndomise an array: @param array: the array to print (read only, so const) @param len: the length of the array, min and , max value to determine the num range
void zeroArray(int *array, int len);                                                                                    // Function to turn all array elements to zero, using 2 params, one for the array, the other for the length of array
void printArray(const int *array, int len);                                                                             // Function to print the array: @param array: the array to fill (an input/output parameter) @param len: the lenght of the array

void setup() {
  Serial.begin(BAUD_RATE);                                                                                              // serial set up
  Serial.println("\nA3_ClickArrays starting...\n");
  Serial.println("\nUse SW1 to modify arrays\n");
  Serial.print("\nClick SW1 to print the two arrays\n");
  Serial.print("\nPress and hold SW1 for approx 2 secs to update Array1 with random values\n");
  Serial.print("\nPress and hold SW1 for more than 3 secs to update Array1 with zeroes\n");
  //Serial.print("\nDouble click SW1 to copy the elements in Array1 to Array2\n");

}

void loop() {
  int i;                                                                                                                // i declared as int
  static int Array1[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};                                                       // Array1 declared
  static int Array2[ARRAY_LEN] = {0};                                                                                   // Array2 declared
  int LENGTH_OF_BUTTON_PRESS;                                                                                           // Length of time the button was pressed for
  const int NORMAL_CLICK_TIME_MS = 999;                                                                                 // times for clicks
  const int HOLD_CLICK_TIME_MS = 3000;
  const int LONG_CLICK_TIME_MS = 3001;
  int MINIMUM_VALUE = 0;                                                                                                // min value dcelared
  int MAXIMUM_VALUE = 99;                                                                                               // max value declared


  if (readSwitchEventTimes(sw1Object, &LENGTH_OF_BUTTON_PRESS) == SW_CLICK) {                                           // was sw1 clicked(with period of time pressed)?
    if (LENGTH_OF_BUTTON_PRESS <= NORMAL_CLICK_TIME_MS) {                                                                 // if so -> if time pressed is less than and equal to 999, print arrays
      Serial.print("\nArray1 =");
      printArray(Array1, ARRAY_LEN);
      Serial.print("Array2 =");
      printArray(Array2, ARRAY_LEN);
    }
    if (LENGTH_OF_BUTTON_PRESS > NORMAL_CLICK_TIME_MS && LENGTH_OF_BUTTON_PRESS <= HOLD_CLICK_TIME_MS) {                  // if length of time pressed is greater than 999 and less than and equal to 3000, randomise first array and print both arrays
      randomizeArray(Array1, ARRAY_LEN, MINIMUM_VALUE, MAXIMUM_VALUE);                                                   // random array function with params for pointer array, length of array, min value and max vlue
      Serial.print("\nRandomised Array1 =");
      printArray(Array1, ARRAY_LEN);
      Serial.print("Array2 =");
      printArray(Array2, ARRAY_LEN);
    }
    if (LENGTH_OF_BUTTON_PRESS >= LONG_CLICK_TIME_MS) {                                                                   // if length of time pressed is greater than adn equal to 3001, turn all elements in Array1 to zero and print both arrays
      zeroArray(Array1, ARRAY_LEN);                                                                                       // zero array function with params of first array and the length of the array
      Serial.print("\nZero Array =");
      printArray(Array1, ARRAY_LEN);
      Serial.print("Array2 =");
      printArray(Array2, ARRAY_LEN);
    }
  }
  delay(SUPERLOOP_DELAY_MS);                                                                                            // delay at end of loop
}

/*
  This functions purpose is to print the array with elements

  @param:  *array        array that will be used
  @param:  len           length of array
  @param:  minVal        minimum value for smallest value in range for random number
  @param:  maxVal        maximum value for largest value in range for random number
*/

void randomizeArray(int *array, int len, int minVal, int maxVal) {                                                      // random array function with params for pointer array, length of array, min value and max vlue
  int i;                                                                                                                // i is declared as a int
  for (int i = 0; i < len; i++)                                                                                         // for loop that points at incrementing indexes in the array and gets a random value of it between min and max value
    *(array + i) = random(minVal, maxVal + 1);                                                                          // array pointer plus the index is equal to the random value between min value and max value + 1
}

/*
  This functions purpose is to print the array with zeroes

  @param:  *array        array that will be used
  @param:  len           length of array
*/

void zeroArray(int *array, int len) {                                                                                   // zero array function with a pointer array param and length of array
  int i;                                                                                                                // i declared as int
  for (i = 0; i < len; i++)                                                                                             // for i iterating over length of array
    *(array + i) = 0;                                                                                                   // element equals zero
}

/*
  This functions purpose is to print the array with elements

  @param:  *array        array that will be printed
  @param:  len           length of array
*/

void printArray(const int *array, int len) {                                                                            // print array function with a constant pointer array and length of array
  int i;                                                                                                                // i is declared as an int

  Serial.print(" {");                                                                                                   // print to mointor

  if (len > 0)                                                                                                          // if length of array is greater than zero, print array index 0
    Serial.print(*array);

  for (i = 1; i < len; i++) {                                                                                           // for loop to iterate through length of array, starting on the first index
    Serial.print(", ");                                                                                                 // prints to monitor
    Serial.print(*(array + i));                                                                                         // print pointer of array ata certain index +increment
  }
  Serial.println("}");
}
