/*
This is simple C code to demonstrate how to use interrupt and data register and data direction
on low level without using Arduino functions. Performance boost from this is minimal but could be
useful in some cases.

*/
#include <Arduino.h>

#define LED 4
#define BTN 2

ISR(INT0_vect) { // ISR
  PORTB ^= (1 << LED); // flip over Port B pin 4 value
}

void setup() {
  DDRB |= _BV(LED); // Set data direction of PORT B 4(LED) to 1 (output)

  DDRD |= _BV(BTN); // Set data direction of PORT D 2(BTN) to 1 (output)
  PORTD |= _BV(BTN); // Set PORT D 2(BTN) to 1 (pull up register)

  EICRA |= (1 << ISC01); // set bit1 of External Interrupt Control Register A to 1
  EICRA &= ~(1 << ISC00); // set bit0 of External Interrupt Control Register A to 0
  
  EIMSK |= (1 << INT0); //External Interrupt Mask Register bit0 to 1
  sei(); // Enable interrupts globally
}

void loop() {
  delay(500); // do other shit.
}

