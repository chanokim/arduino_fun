#include <Arduino.h>

#define LED 4
#define BTN 2

ISR(INT0_vect) {
  PORTB ^= (1 << LED);
}

void setup() {
  Serial.begin(9600);
  DDRB |= _BV(LED);

  DDRD |= _BV(BTN);
  PORTD |= _BV(BTN);

  DDRB |= _BV(LED_BUILTIN);
  PORTB &= ~_BV(LED_BUILTIN);
  
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  
  EIMSK |= (1 << INT0);
  sei();
}

void loop() {
  delay(500);
}

