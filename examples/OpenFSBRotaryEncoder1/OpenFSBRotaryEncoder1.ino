/**
*   openFSB.org
*
*   OpenFSBRotaryEncoder example 1
*
*   Methods used:
*   - update()
*   - rotatingCW()
*   - rotatingCCW()
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
  if ( encoder.rotatingCW() ) {
    Serial.println( "Turned clockwise" );
  }
  if ( encoder.rotatingCCW() ) {
    Serial.println( "Turned counterclockwise" );
  }
}
