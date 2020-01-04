/**
*   openFSB.org
*
*   Class: OpenFSBDebouncer
*
*   Documentation: http://docs-debounced-controls-arduino.openfsb.org
*
**/

#include "OpenFSBDebouncer.h"


// CONSTRUCTORS
OpenFSBDebouncer::OpenFSBDebouncer() {}

OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin ) {
	initDebouncer( pin, pin_mode, getState( ON_STATE ) );
}

OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin, uint8_t mode ) {
	initDebouncer( pin, mode, getState( ON_STATE ) );
}

OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin, uint8_t mode, uint8_t onState ) {
	initDebouncer( pin, mode, onState );
}




// METHODS
uint8_t  OpenFSBDebouncer::getOnState() {
	return getState( ON_STATE );
}


void OpenFSBDebouncer::setIntervalMS( uint16_t intervalMS ) {
	stable_interval_ms = intervalMS;
}


uint16_t OpenFSBDebouncer::getIntervalMS() {
	return stable_interval_ms;
}


int OpenFSBDebouncer::getValue() {
        return (int)getState( DEBOUNCED_STATE );
}


bool OpenFSBDebouncer::switchingOn() {
  return getState( DEBOUNCED_STATE ) == getState( ON_STATE ) && getState( DEBOUNCED_STATE_CHANGED );
}


bool OpenFSBDebouncer::switchingOff() {
  return getState( DEBOUNCED_STATE ) != getState( ON_STATE ) && getState( DEBOUNCED_STATE_CHANGED );
}


bool  OpenFSBDebouncer::switching() {
	return getState( DEBOUNCED_STATE_CHANGED );
}


bool OpenFSBDebouncer::isOn() {
  return getState( DEBOUNCED_STATE ) == getState( ON_STATE );
}


bool OpenFSBDebouncer::isOff() {
  return getState( DEBOUNCED_STATE ) != getState( ON_STATE );
}


bool OpenFSBDebouncer::rose() {
        return getState( DEBOUNCED_STATE ) && getState( DEBOUNCED_STATE_CHANGED );
}


bool OpenFSBDebouncer::fell() {
        return ( !getState( DEBOUNCED_STATE ) ) && getState( DEBOUNCED_STATE_CHANGED );
}


bool OpenFSBDebouncer::isLow() {
        return getState( DEBOUNCED_STATE ) == LOW;
}


bool OpenFSBDebouncer::isHigh() {
        return getState( DEBOUNCED_STATE ) == HIGH;
}


void OpenFSBDebouncer::update() {
	if ( !initialized ) return;                            // nothing to do
	unsetState( DEBOUNCED_STATE_CHANGED );
	pin_value = digitalRead( pin_number );
	if (pin_value != getState( UNSTABLE_STATE ) ) {        // bouncing?
		toggleState( UNSTABLE_STATE );
		resetRtimer(); // restart stable state wait timer
	}
	else {
		if ( getRtimerMS() >= stable_interval_ms ) {         // no bounce anymore
			if ( pin_value != getState( DEBOUNCED_STATE ) ) {  // new state?
				toggleState( DEBOUNCED_STATE );
				setState( DEBOUNCED_STATE_CHANGED );
			}
		}
	}
}


// PRIVATE METHODS
void OpenFSBDebouncer::initDebouncer( uint8_t pin, uint8_t mode, uint8_t onState ) {
	pin_number = pin;
	pin_mode = mode;

	switch ( pin_mode ) {
		case PULLUP:
			pinMode( pin_number, INPUT_PULLUP );
			setOnState( LOW );
			initialized = true;
			break;
#ifdef PULLDOWN
		case PULLDOWN:
			pinMode( pin_number, INPUT_PULLDOWN );
			setOnState( HIGH );
			initialized = true;
			break;
#endif
		case EXTERNAL:
			pinMode( pin_number, INPUT );
			setState( ON_STATE );
			initialized = true;
			break;
		default:  // wrong mode
				break;
	}

	resetRtimer();
}


void OpenFSBDebouncer::setOnState( uint8_t onState ) {
	if ( pin_mode == EXTERNAL ) {
		if (onState == HIGH) setState( ON_STATE );
		if (onState == LOW)  unsetState( ON_STATE );
	}
}


void OpenFSBDebouncer::setState( byte bits ) {
  state |= bits;
}


void OpenFSBDebouncer::unsetState( byte bits ) {
  state &= ~bits;
}


void OpenFSBDebouncer::toggleState( byte bits ) {
   state ^= bits;
}


byte OpenFSBDebouncer::getState( byte bits ) {
	return ( state & bits ) != 0;
}


void OpenFSBDebouncer::resetRtimer() {
	rtimer_start_time_ms = millis();
}


unsigned long OpenFSBDebouncer::getRtimerMS() {
	return millis() - rtimer_start_time_ms;
}
