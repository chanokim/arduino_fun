/*
This is simple C code to demonstrate how to use interrupt and data register and data direction
on low level without using Arduino functions. Performance boost from this is minimal but could be
useful in some cases.

*/
#include <Arduino.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

#define LED 4
#define BTN 2

static const int DHT_SENSOR_PIN = 8;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

ISR(INT0_vect) { // ISR
  PORTB ^= (1 << LED); // flip over Port B pin 4 value
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity ) {
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul ) {
    if( dht_sensor.measure( temperature, humidity ) == true ) {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}

void setup() {
  Serial.begin( 9600);
  DDRB |= _BV(LED); // Set data direction of PORT B 4(LED) to 1 (output)

  DDRD |= _BV(BTN); // Set data direction of PORT D 2(BTN) to 1 (output)
  PORTD |= _BV(BTN); // Set PORT D 2(BTN) to 1 (pull up register)

  EICRA |= (1 << ISC01); // set bit1 of External Interrupt Control Register A to 1
  EICRA &= ~(1 << ISC00); // set bit0 of External Interrupt Control Register A to 0
  
  EIMSK |= (1 << INT0); //External Interrupt Mask Register bit0 to 1
  sei(); // Enable interrupts globally
}

void loop() {
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true ) {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }
}

