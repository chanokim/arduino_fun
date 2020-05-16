#include <Arduino.h>

const unsigned int latch = 9;  //74HC595  pin 9 STCP
const unsigned int clk = 10; //74HC595  pin 10 SHCP
const unsigned int data = 8;   //74HC595  pin 8 DS

const unsigned int digit1 = 4; // pin for 1st digit of 4 digit led display
const unsigned int digit2 = 5; // pin for 2nd digit
const unsigned int digit3 = 6; // pin for 3rd digit
const unsigned int digit4 = 7; // pin for 4th digit

const unsigned int switch1 = 11; // pin for switch1
const unsigned int switch2 = 12; // pin for switch2

const unsigned int FLASH_FREQ = 5; // How often we will flash LED
char fourdigits[4];
int speed = 2;

void displayDigit(unsigned int place, unsigned int num);
void strToZeroPaddedNum(unsigned int num);
void displayFourDigits(const char fourdigits[], int loop);
// bit to LED mapping from LSB
// +-0-+
// |   |
// 5   1
// |   |
// +-6-+
// |   |
// 4   2
// |   |
// +-3-+  7

unsigned char table[]= {
  0x3f, //B0011 1111 (0)
  0x06, //B0000 0110 (1)
  0x5b, //B0101 1011 (2)
  0x4f, //B0100 1111 (3)
  0x66, //B0110 0110 (4)
  0x6d, //B0110 1101 (5)
  0x7d, //B0111 1101 (6)
  0x07, //B0000 0111 (7)
  0x7f, //B0111 1111 (8)
  0x6f, //B0110 1111 (9)
  0x77, //B0111 0111 (A)
  0x7c, //B0111 1100 (b)
  0x39, //B0011 1001 (c)
  0x5e, //B0101 1110 (d)
  0x79, //B0111 1001 (E)
  0x71, //B0111 0001 (F)
  0x39, //B0011 1001 (G) Same as C, indistinguishiable
  0x76, //B0111 0110 (H)
  0x30, //B0011 0000 (I)
  0x16, //B0001 0110 (J)
  0x76, //B0111 0110 (K) Same as H, indistinguishiable
  0x38, //B0011 1000 (L)
  0x34, //B0101 0100 (n)
  0x3b, //B0101 1100 (o)
  0x73, //B0111 0011 (P)
  0x50, //B0101 0000 (r)
  0x6d, //B0110 1101 (S)
  0x31, //B0011 0001 (T) looks like inverse 7, rather not use it
  0x3e, //B0011 1110 (U)
  0x3e, //B0011 1110 (V) same as U, indistinguishiable
  0x3e, //B0011 1110 (W) same as U, rhter not use it
  0x76, //B0111 0110 (x) same as H, rhter not use it
  0x6e, //B0110 1110 (y) 
  0x5b, //B0101 1011 (Z) same as 2, indistinguishiable
  0x00}; //Display digital data

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(data,OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
}

void loop() {
  unsigned int i = 0;
  for (i = 0; i < 9999; i++) { // Seven-Segment LED needs to be flashed as it fades out.
    strToZeroPaddedNum(i); // converts integer to string
    displayFourDigits(fourdigits, speed); // displays digits to LED
    if(digitalRead(switch1) == LOW) speed++; // 
    if(digitalRead(switch2) == LOW && speed > 1) speed--;
  }
}

void displayDigit(unsigned int place, unsigned int num){
  switch(place) {
    case 0:
      digitalWrite(digit1, LOW);
      digitalWrite(digit2, HIGH);
      digitalWrite(digit3, HIGH);
      digitalWrite(digit4, HIGH);
      break;
    case 1:
      digitalWrite(digit1, HIGH);
      digitalWrite(digit2, LOW);
      digitalWrite(digit3, HIGH);
      digitalWrite(digit4, HIGH);
      break;
    case 2:
      digitalWrite(digit1, HIGH);
      digitalWrite(digit2, HIGH);
      digitalWrite(digit3, LOW);
      digitalWrite(digit4, HIGH);
      break;
    case 3:
      digitalWrite(digit1, HIGH);
      digitalWrite(digit2, HIGH);
      digitalWrite(digit3, HIGH);
      digitalWrite(digit4, LOW);
      break;
  }
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, table[num]);
  digitalWrite(latch, HIGH);
  delay(FLASH_FREQ);
}

void strToZeroPaddedNum(unsigned int num) {
  sprintf(fourdigits, "%04d", num);
}

void displayFourDigits(const char fourdigits[], int loop) {
  int cnt = 0;
  for(cnt = 0; cnt < loop; cnt++) {
    displayDigit(0, fourdigits[0] - '0');
    displayDigit(1, fourdigits[1] - '0');
    displayDigit(2, fourdigits[2] - '0');
    displayDigit(3, fourdigits[3] - '0');    
  }
}

