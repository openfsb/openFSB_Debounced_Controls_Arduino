#ifndef OPENFSB_ROTARY_ENCODER_H
#define OPENFSB_ROTARY_ENCODER_H

#include <Arduino.h>
#include "OpenFSBDebouncer.h"

#define ROTARY_ENCODER_DIRECTION_NONE    0
#define ROTARY_ENCODER_DIRECTION_CW      1
#define ROTARY_ENCODER_DIRECTION_CCW     2

#define ROTARY_ENCODER_DEFAULT_SEQUENCE  0b00000000


class OpenFSBRotaryEncoder {
	public:
		//Constructor
		OpenFSBRotaryEncoder( uint8_t pinA, uint8_t pinB );
		OpenFSBRotaryEncoder( uint8_t pinA, uint8_t pinB, uint8_t mode );
		OpenFSBRotaryEncoder( uint8_t pinA, uint8_t pinB, uint8_t mode, uint8_t onState );

		//Methods
		uint8_t  getOnState();
		void     setIntervalMS( uint16_t intervalMS );
		uint16_t getIntervalMS();
		int      getDirection();
		bool     rotatingCW();
		bool     rotatingCCW();
		void     update();
		long     read();


	private:
		//Methods
		void  initRotaryEncoder( uint8_t pinA, uint8_t pinB, uint8_t mode, uint8_t onState );
		void  updateDirection();

		//Attributes
		OpenFSBDebouncer  debouncerA = OpenFSBDebouncer();
		OpenFSBDebouncer  debouncerB = OpenFSBDebouncer();
		uint8_t           sequence   = ROTARY_ENCODER_DEFAULT_SEQUENCE;
		uint8_t           direction  = ROTARY_ENCODER_DIRECTION_NONE;
		long              counter    = 0;

};


#endif
