/**
*   openFSB.org
*
*   Class: OpenFSBRotaryEncoder
*
*   Documentation: http://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <OpenFSBRotaryEncoder.h>


// CONSTRUCTORS
OpenFSBRotaryEncoder::OpenFSBRotaryEncoder(  uint8_t pinA, uint8_t pinB  ) {
	debouncerA.setPin( pinA );
	debouncerB.setPin( pinB );
}

OpenFSBRotaryEncoder::OpenFSBRotaryEncoder( uint8_t pinA, uint8_t pinB, uint8_t mode ) {
	debouncerA.setPin( pinA );
	debouncerB.setPin( pinB );
	debouncerA.setMode( mode );
	debouncerB.setMode( mode );
}

OpenFSBRotaryEncoder::OpenFSBRotaryEncoder( uint8_t pinA, uint8_t pinB, uint8_t mode, uint8_t onState ) {
	debouncerA.setPin( pinA );
	debouncerB.setPin( pinB );
	debouncerA.setMode( mode );
	debouncerB.setMode( mode );
	debouncerA.setOnState( onState  );
	debouncerB.setOnState( onState  );
}



// METHODS
void OpenFSBRotaryEncoder::begin() {
	debouncerA.begin();
	debouncerB.begin();
}


uint8_t OpenFSBRotaryEncoder::getOnState() {
	return debouncerA.getOnState();
}


void OpenFSBRotaryEncoder::setIntervalMS( uint16_t intervalMS ) {
	debouncerA.setIntervalMS( intervalMS );
	debouncerB.setIntervalMS( intervalMS );
}


uint16_t OpenFSBRotaryEncoder::getIntervalMS() {
	return debouncerA.getIntervalMS();
}


int OpenFSBRotaryEncoder::getDirection() {
	if ( direction == ROTARY_ENCODER_DIRECTION_CW)  return  1;
	if ( direction == ROTARY_ENCODER_DIRECTION_CCW) return -1;
	return 0;
}


bool OpenFSBRotaryEncoder::rotatingCW() {
	return direction == ROTARY_ENCODER_DIRECTION_CW;
}


bool OpenFSBRotaryEncoder::rotatingCCW() {
	return direction == ROTARY_ENCODER_DIRECTION_CCW;
}


/**
*   Update the state of the rotary encoder with error detection.
*   When a pulse is missed there will be a wrong sequence. By resetting
*   the sequenc each time starting moving to the next detent, any wrong
*   sequence will be removed. Each detent there are two reset events so
*   one of them may be missed.
*
*   Sequence bits:  rr0000ss
*                   ||    |+- state pin B
*                   ||    +- state pin A
*                   |+- pin B is read
*                   +- pin A is Read
*
*   Direction CW:
*                   00000000  reset sequence (triggerd by pin B)
*                   00000000  reset sequence (triggerd by pin A)
*                   01000001  pin B read --> do nothing
*                   11000001  pin A read --> direction CW
*
*   Direction CCW:
*                   00000000  reset sequence (triggerd by pin A)
*                   00000000  reset sequence (triggerd by pin B)
*                   10000010  pin A read --> do nothing
*                   11000010  pin B read --> direction CCW
*
*   Direction CW with missed pulses:
*                   missed trigger pin B
*                   00000000  reset sequence (triggerd by pin A)
*                   01000001  pin B read --> do nothing
*                   11000001  pin A read --> direction CW
*                   00000000  reset sequence (triggerd by pin B)
*                   00000000  reset sequence (triggerd by: pin A)
*                   01000001  pin B read --> do nothing
*                   missed pin A         --> detent with no event
*                   00000000  reset sequence (triggerd by pin B)
*                   00000000  reset sequence (triggerd by: pin A)
*                   01000001  pin B read --> do nothing
*                   11000001  pin A read --> direction CW
*
**/
void OpenFSBRotaryEncoder::update() {
	debouncerA.update();
	debouncerB.update();
	direction = ROTARY_ENCODER_DIRECTION_NONE;
  // Reset sequence when pins are switching to "on" (first pulses).
	// Any wrong sequence because of missed pulses will be removed.
	// There are two chances to reset, so no problem when one pulse is missed.
	if ( debouncerA.switchingOn() || debouncerB.switchingOn() ) sequence = ROTARY_ENCODER_DEFAULT_SEQUENCE;
  // Read opposite pin when pins are switching to "off" (last pulses).
	if ( debouncerA.switchingOff() ) {
		sequence |= debouncerB.isOn() ? 0b00000001 : 0 ;  // read pinB
		sequence |= 0b01000000; // set pinB is read
		updateDirection();
	}
	if ( debouncerB.switchingOff() ) {
		sequence |= debouncerA.isOn() ? 0b00000010 : 0 ;  // read PinA
		sequence |= 0b10000000; // set pinA is read
		updateDirection();
	}
}


long OpenFSBRotaryEncoder::read() {
	update();
	return counter;
}



// PRIVATE METHODS
void OpenFSBRotaryEncoder::updateDirection() {
	if ( sequence == 0b11000001 ) {         // both pins read ("11") and rotating CW ("01")
		direction = ROTARY_ENCODER_DIRECTION_CW;
		counter++;
		sequence = ROTARY_ENCODER_DEFAULT_SEQUENCE;  // reset sequence
	}
	else if ( sequence == 0b11000010 ) {    // both pins read ("11") and rotating CCW ("10")
		direction = ROTARY_ENCODER_DIRECTION_CCW;
		counter--;
		sequence = ROTARY_ENCODER_DEFAULT_SEQUENCE;  // reset sequence
	}
}
