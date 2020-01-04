/**
*   openFSB.org
*
*   OpenFSBButton example with absolute mode
*
*   Methods used:
*   - press()
*   - release()
*
*   Documentation: https://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <OpenFSBButton.h>


#define BUTTON_PIN   2

OpenFSBButton button( BUTTON_PIN );


void setup() {
  Serial.begin( 115200 );
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );
}


void loop() {
  button.update();
  if ( button.press() ) {
    digitalWrite( LED_BUILTIN, HIGH );
    Serial.println( "Press" );
  }
  if ( button.release() ) {
    digitalWrite( LED_BUILTIN, LOW );
    Serial.println( "Release" );
  }
}
