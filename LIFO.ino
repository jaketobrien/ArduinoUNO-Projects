/*  Author: Jake O'Brien
    Date: 28/04/21
    This code's purpose is to add or remove to LIFO buffer, depending on wether SW1 or SW2 is clicked and then print the arrays with the amount of used slots
*/

#include <ee108.h>

const int SUPERLOOP_DELAY_MS = 50;                                                // delay between loops
const int BAUD_RATE = 9600;                                                       // Baud rate set
const int LIFO_LEN = 5;                                                           // Lifo buffer length set to 5
int LOOP_COUNT = 0;

void addToLifo(int *LIFO_BUFFER, int USED_SLOTS, int RANDOM_NUM);                 // function to add to lifo, params are: the pointer lifo buffer, used slots and random num
void removeFromLifo(int *LIFO_BUFFER, int *USED_SLOTS, int *REMOVED_NUM);         // function to remove from lifo, params are: pointer lifo buffer, pointer used slots, pointer removed number
void PrintSlots(int *LIFO_BUFFER, int USED_SLOTS);                                // function to print slots, params are: pointer lido buffer, and used slots

void setup() {
  Serial.begin(BAUD_RATE);                                                        // Serial set up
  Serial.println("\nA3_LIFO starting...\n");
  Serial.println("\nClick SW1 to start\n");

}

void loop() {
  static int LIFOarray[LIFO_LEN] = {};                                             // variable for fifo buffer (array) with a variable length and equal to empty curly  brackets
  static int USED_SLOTS = 0;                                                       // used slots set to zero
  static int FREE_SLOTS = LIFO_LEN - USED_SLOTS;                                   // free slots is length of lifo - used slots
  int MINIMUM_VALUE = 0;                                                           // min and max value set
  int MAXIMUM_VALUE = 99;
  int RANDOM_NUMBER = random(MINIMUM_VALUE, MAXIMUM_VALUE);                        // random num of range between min and max value
  int REMOVED_NUMBER;
  int i = 0;                                                                       // int i set as zero

  if (readSwitchEvent(sw1Object) == SW_CLICK) {                                    // if sw1 is clicked, check if full, if not...
    Serial.print("Loop ");                                                       // loop count
    Serial.print(LOOP_COUNT);
    Serial.print(":");
    Serial.print(" [SW1 Clicked],");
    if (USED_SLOTS < LIFO_LEN) {                                                 // if used slots is less than length of lifo, run functions
      addToLifo(LIFOarray, USED_SLOTS, RANDOM_NUMBER);
      USED_SLOTS = USED_SLOTS + 1;
      Serial.print(RANDOM_NUMBER);                                               // print num added and array
      Serial.print(" was added to buffer");
      PrintSlots(LIFOarray, USED_SLOTS);
    }
    else {
      Serial.print(" can't add to buffer --");
      Serial.println(" buffer is full!!");                                        // else, its full
    }
  }
  if (readSwitchEvent(sw2Object) == SW_CLICK) {                                   // if sw2 is clicked, check if greater than 0, if so...
    Serial.print("Loop ");                                                        // loop count
    Serial.print(LOOP_COUNT);
    Serial.print(":");
    Serial.print(" [SW2 Clicked],");
    if (USED_SLOTS > 0) {
      removeFromLifo(LIFOarray, &USED_SLOTS, &REMOVED_NUMBER);                     // run functions, with address at used slots and removed number
      Serial.print(REMOVED_NUMBER);                                                // print removed num and array
      Serial.print(" was removed from buffer");
      PrintSlots(LIFOarray, USED_SLOTS);
    }
    else {
      Serial.print(" can't add to buffer --");
      Serial.println(" buffer is empty!!");                                         // else, is empty
    }
  }

  delay(SUPERLOOP_DELAY_MS);                                                        // loop delay
  LOOP_COUNT++;
}

/*
   This functions purpose is to add to the next index of the buffer

   @param:  *LIFO_BUFFER        LIFO buffer that the number will be added to
   @param:  *USED_SLOTS         variable that contains the amount of used values in the buffer
   @param:  *RANDOM_NUM         variable that is the random number
*/

void addToLifo(int *LIFO_BUFFER, int USED_SLOTS, int RANDOM_NUM) {                  // function to add to lifo, params are: the pointer lifo buffer, used slots and random num
  *(LIFO_BUFFER + USED_SLOTS) = RANDOM_NUM;                                         // pointer of lifo buffer + used slots is equal to rand num
}

/*
   This functions purpose is to remove the last number of the buffer, return that number
   and print it

   @param:  *LIFO_BUFFER        LIFO buffer that the number will be removed from
   @param:  *USED_SLOTS         variable that contains the amount of used values in the buffer
   @param:  *REMOVED_NUM        variable that is the removed number
*/

void removeFromLifo(int *LIFO_BUFFER, int *USED_SLOTS, int *REMOVED_NUM) {          // function to remove from lifo, params are: pointer used slots
  int INDEX_OF_ARRAY = *USED_SLOTS;                                                 // INDEX_OF_ARRAY decalred and let equal to the pointer of USED_SLOTS (position of index)
  *REMOVED_NUM = *(LIFO_BUFFER + INDEX_OF_ARRAY - 1);                               // removed num is the buffer + the index length-1, as it remembers the value there
  *USED_SLOTS = INDEX_OF_ARRAY - 1;                                                 // reduces number of used slots by the index-1
}

/*
  This functions purpose is to print the buffer with elements

  @param:  *LIFO_BUFFER        LIFO buffer that will be printed with elements
  @param:  *USED_SLOTS         variable that contains the amount of used values in the buffer
*/

void PrintSlots(int *LIFO_BUFFER, int USED_SLOTS) {                                 // function to print slots, params are: pointer lido buffer, and used slots
  int i;

  Serial.print(", buffer is now");
  Serial.print(" {");                                                               // print to mointor

  if (USED_SLOTS > 0)                                                               // if length of array is greater than zero, print array index 0
    Serial.print(*LIFO_BUFFER);

  for (i = 1; i < USED_SLOTS; i++) {                                                // for loop to iterate through length of array, starting on the first index
    Serial.print(", ");                                                             // prints to monitor
    Serial.print(*(LIFO_BUFFER + i));                                               // print pointer of array ata certain index +increment
  }
  Serial.print("}, ");
  Serial.print(USED_SLOTS);                                                         // used slots printed
  Serial.println(" used");
}
