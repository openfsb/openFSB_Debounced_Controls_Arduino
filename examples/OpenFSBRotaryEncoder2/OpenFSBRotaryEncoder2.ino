/**
*   openFSB.org
*
*   OpenFSBRotaryEncoder example 1
*
*   Methods used:
*   - update()
*   - getDirection()
*
*   Documentation: https://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <OpenFSBRotaryEncoder.h>


#define ENCODER_PIN_A   2
#define ENCODER_PIN_B   3

OpenFSBRotaryEncoder encoder( ENCODER_PIN_A, ENCODER_PIN_B );  // Defaults: mode=PULLUP, onState=LOW


void setup() {
      Serial.begin( 115200 );
}


void loop() {
  encoder.update();
  if ( encoder.getDirection() == 1 ) {
    Serial.println( "Turned clockwise" );
  }
  if ( encoder.getDirection() == -1 ) {
    Serial.println( "Turned counterclockwise" );
  }
}
