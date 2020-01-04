/**
*   openFSB.org
*
*   OpenFSBDebouncer example with absolute mode
*
*   Methods used:
*   - fell()
*   - rose()
*
*   Documentation: https://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <OpenFSBDebouncer.h>


#define DEBOUNCER_PIN   2

OpenFSBDebouncer debouncer( DEBOUNCER_PIN );   // Defaults: mode=PULLUP, onState=LOW
// For PULLDOWN (built-in resistor):
//OpenFSBDebouncer debouncer( DEBOUNCER_PIN, PULLDOWN );  // Defaults: onState=HIGH
// For PULLDOWN (external resistor):
//OpenFSBDebouncer debouncer( DEBOUNCER_PIN, EXTERNAL, HIGH );  // Defaults: none


void setup() {
  Serial.begin( 115200 );
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );
}


void loop() {
  debouncer.update();

  // For PULLUP:
  if ( debouncer.fell() ) {
    digitalWrite( LED_BUILTIN, HIGH );
    Serial.println( "Switching on" );
  }
  if ( debouncer.rose() ) {
    digitalWrite( LED_BUILTIN, LOW );
    Serial.println( "Switching off" );
  }

  // For PULLDOWN:
  /*
  if ( debouncer.rose() ) {
    digitalWrite( LED_BUILTIN, HIGH );
    Serial.println( "Switching on" );
  }
  if ( debouncer.fell() ) {
    digitalWrite( LED_BUILTIN, LOW );
    Serial.println( "Switching off" );
  }
  */
}
