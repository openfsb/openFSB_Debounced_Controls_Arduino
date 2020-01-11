/**
*   openFSB.org
*
*   OpenFSBRotaryEncoder example 1
*
*   Method used:
*   - read()
*
*   Documentation: https://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <OpenFSBRotaryEncoder.h>


#define ENCODER_PIN_A   2
#define ENCODER_PIN_B   3

OpenFSBRotaryEncoder encoder( ENCODER_PIN_A, ENCODER_PIN_B );  // Defaults: mode=PULLUP, onState=LOW

long lastCounter = 0;


void setup() {
      Serial.begin( 115200 );
}


void loop() {
  int counter = encoder.read();
  if ( counter > lastCounter ) {
    lastCounter = counter;
    Serial.print( "Turned clockwise * " );
    Serial.println( counter );
  }
  if ( counter < lastCounter ) {
    lastCounter = counter;
    Serial.print( "Turned counterclockwise * " );
    Serial.println( counter );
  }
}
