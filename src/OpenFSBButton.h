#ifndef OPENFSB_BUTTON_H
#define OPENFSB_BUTTON_H

/**
*   openFSB.org
*
*   Documentation: http://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <Arduino.h>
#include "OpenFSBDebouncer.h"


class OpenFSBButton {
	public:
		//Constructor
		OpenFSBButton( uint8_t pin );
		OpenFSBButton( uint8_t pin, uint8_t mode );
		OpenFSBButton( uint8_t pin, uint8_t mode, uint8_t onState );

		//Methods
		uint8_t  getOnState();
		void     setIntervalMS( uint16_t intervalMS );
		uint16_t getIntervalMS();
		int      getValue();
		bool     press();
    bool     release();
    bool     isPressed();
    bool     isReleased();
		bool     rose();
		bool     fell();
		bool     isLow();
		bool     isHigh();
		void     update();

	private:
		//Methods
		void  initButton( uint8_t pin, uint8_t mode, uint8_t onState );

		//Attributes
		OpenFSBDebouncer  debouncer = OpenFSBDebouncer();

};


#endif
