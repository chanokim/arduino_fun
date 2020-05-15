#include <Arduino.h>

//www.elegoo.com
//2016.12.12

int latch=9;  //74HC595  pin 9 STCP
int clk=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int control1 = 4;
int control2 = 5;
int control3 = 6;
int control4 = 7;

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};//Display digital data

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(control1, OUTPUT);
  pinMode(control2, OUTPUT);
  pinMode(control3, OUTPUT);
  pinMode(control4, OUTPUT);
}
/*   The most common method of using 74CH595
 *   latch->LOW : Begin transmitting signals.
 *   shiftOut(dataPin, clockPin, bitOrder, value)
 *   dataPin: the pin on which to output each bit. Allowed data types: int.
 *   clockPin: the pin to toggle once the dataPin has been set to the correct value. Allowed data types: int.
 *   bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST. (Most Significant Bit First, or, Least Significant Bit First).
 *   value: the data to shift out. Allowed data types: byte. 
 *   latch->HIch : The end of the transmission signal.
*/
void Display(unsigned char num, unsigned char delay1) {
  digitalWrite(control1, LOW);
  digitalWrite(control2, HIGH);
  digitalWrite(control3, HIGH);
  digitalWrite(control4, HIGH);

  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, table[num]);
  digitalWrite(latch, HIGH);
  delay(delay1);
  
  digitalWrite(control1, HIGH);
  digitalWrite(control2, LOW);
  digitalWrite(control3, HIGH);
  digitalWrite(control4, HIGH);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, table[num+1]);
  digitalWrite(latch, HIGH);
  delay(delay1);

  digitalWrite(control1, HIGH);
  digitalWrite(control2, HIGH);
  digitalWrite(control3, LOW);
  digitalWrite(control4, HIGH);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, table[num+2]);
  digitalWrite(latch, HIGH);
  delay(delay1);

  digitalWrite(control1, HIGH);
  digitalWrite(control2, HIGH);
  digitalWrite(control3, HIGH);
  digitalWrite(control4, LOW);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, table[num+3]);
  digitalWrite(latch, HIGH);
  delay(delay1);
}
void loop() {
  unsigned char i = 0;
  for(i = 0; i < 100; i++) {
    Display(1, 5);  
  }
  for(i = 0; i < 100; i++) {
    Display(2, 5);
  }
  for(i = 0; i < 100; i++) {
    Display(3, 5);
  }
  for(i = 0; i < 100; i++) {
    Display(4, 5);
  }
//  Display(4);
//  delay(500);
//  Display(5);
//  delay(500);
//  Display(6);
//  delay(500);
//  Display(7);
//  delay(500);
//  Display(8);
//  delay(500);
//  Display(9);
//  delay(500);
//  Display(10);
//  delay(500);
//  Display(11);
//  delay(500);
//  Display(12);
//  delay(500);
//  Display(13);
//  delay(500);
//  Display(14);
//  delay(500);
//  Display(15);
//  delay(500);
}