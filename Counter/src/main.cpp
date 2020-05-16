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

const unsigned int FLASH_FREQ = 5;
char fourdigits[4];
int speed = 2;

void displayDigit(unsigned int place, unsigned int num);
void strToZeroPaddedNum(unsigned int num);
void displayFourDigits(const char fourdigits[], int loop);

unsigned char table[]= {
  0x3f, //B0011 1111 (0)
  0x06, //B0000 0110 (1)
  0x5b, //B0101 1011 (2)
  0x4f, //B0100 1111 (3)
  0x66,
  0x6d,
  0x7d,
  0x07,
  0x7f,
  0x6f,
  0x77,
  0x7c,
  0x39,
  0x5e,
  0x79,
  0x71,
  0x00}; //Display digital data

void setup() {
  Serial.begin(9600);
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
  for (i = 0; i < 9999; i++) {
    strToZeroPaddedNum(i);
    // Serial.print("fourdigits=");
    // Serial.println(fourdigits);
    displayFourDigits(fourdigits, speed);
    if(digitalRead(switch1) == LOW) {
      speed++;
      // Serial.print("speed=");
      // Serial.println(speed);
    }
    if(digitalRead(switch2) == LOW && speed > 1) {
      speed--;
      // Serial.print("speed=");
      // Serial.println(speed);
    }
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
  // Serial.print("fourdigits=");
  // Serial.println(fourdigits);
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

