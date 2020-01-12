/**
*   openFSB.org
*
*   Class: OpenFSBButton
*
*   Documentation: http://docs-debounced-controls-arduino.openfsb.org
*
**/

#include "OpenFSBButton.h"


// CONSTRUCTORS
OpenFSBButton::OpenFSBButton( uint8_t pin ) {
  debouncer.setPin( pin );
}

OpenFSBButton::OpenFSBButton( uint8_t pin, uint8_t mode ) {
  debouncer.setPin( pin );
  debouncer.setMode( mode );
}

OpenFSBButton::OpenFSBButton( uint8_t pin, uint8_t mode, uint8_t onState ) {
  debouncer.setPin( pin );
  debouncer.setMode( mode );
  debouncer.setOnState( onState  );
}



// METHODS
void OpenFSBButton::begin() {
  debouncer.begin();
}


uint8_t OpenFSBButton::getOnState() {
	return debouncer.getOnState();
}


void OpenFSBButton::setIntervalMS( uint16_t intervalMS ) {
	debouncer.setIntervalMS( intervalMS );
}


uint16_t OpenFSBButton::getIntervalMS() {
	return debouncer.getIntervalMS();
}


int OpenFSBButton::getValue() {
	return debouncer.getValue();
}


bool OpenFSBButton::press() {
  return debouncer.switchingOn();
}


bool OpenFSBButton::release() {
  return debouncer.switchingOff();
}


bool OpenFSBButton::isPressed() {
  return debouncer.isOn();
}


bool OpenFSBButton::isReleased() {
  return debouncer.isOff();
}


bool OpenFSBButton::rose() {
	return debouncer.rose();
}


bool OpenFSBButton::fell() {
	return debouncer.fell();
}


bool OpenFSBButton::isLow() {
	return debouncer.isLow();
}


bool OpenFSBButton::isHigh() {
	return debouncer.isHigh();
}


void OpenFSBButton::update() {
	debouncer.update();
}



// PRIVATE METHODS
