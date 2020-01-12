#ifndef OPENFSB_DEBOUNCER_H
#define OPENFSB_DEBOUNCER_H

/**
*   openFSB.org
*
*   Documentation: http://docs-debounced-controls-arduino.openfsb.org
*
**/

#include <Arduino.h>


#define DEBOUNCED_STATE              0x01
#define DEBOUNCED_STATE_CHANGED      0x02
#define UNSTABLE_STATE               0x04
#define ON_STATE                     0x08

#ifndef PULLUP
#define PULLUP          0xF9
#endif
#ifdef INPUT_PULLDOWN
#ifndef PULLDOWN
#define PULLDOWN        0xFA
#endif
#endif
#ifndef EXTERNAL
#define EXTERNAL        0xFB
#endif

#define DEBOUNCER_DEFAULT_STABLE_INTERVAL_MS   2
#define DEBOUNCER_DEFAULT_PIN_MODE             PULLUP


class OpenFSBDebouncer {
	public:
		//Constructor
		OpenFSBDebouncer( uint8_t pin );
		OpenFSBDebouncer( uint8_t pin, uint8_t mode );
		OpenFSBDebouncer( uint8_t pin, uint8_t mode, uint8_t onState );

		//Methods
		void     begin();
		uint8_t  getOnState();
		void     setIntervalMS( uint16_t intervalMS );
		uint16_t getIntervalMS();
		int      getValue();
		bool     switchingOn();
		bool     switchingOff();
		bool     switching();
		bool     isOn();
		bool     isOff();
		bool     rose();
		bool     fell();
		bool     isLow();
		bool     isHigh();
		void     update();

	protected:

	private:
		//Constructor
		OpenFSBDebouncer(); // only for friend classes

		//Methods
		void           setPin( uint8_t pin );
		void           setMode( uint8_t mode );
		void           setOnState( uint8_t onState );
		void           setState( byte bits );
		void           unsetState( byte bits );
		void           toggleState( byte bits );
		byte           getState( byte bits );
		void           resetRtimer();
		unsigned long  getRtimerMS();

		//Attributes
		bool           pin_set               = false;
		bool           initialized           = false;
		uint8_t        pin_number            = 0;
		uint8_t        pin_value             = HIGH;
		uint8_t        pin_mode              = DEBOUNCER_DEFAULT_PIN_MODE;
		uint8_t        state                 = 0x05;
		unsigned long  previous_time_ms      = 0;
		uint16_t       stable_interval_ms    = DEBOUNCER_DEFAULT_STABLE_INTERVAL_MS;
		unsigned long  rtimer_start_time_ms  = 0;

	friend class OpenFSBButton;
	friend class OpenFSBRotaryEncoder;
	//friend class OpenFSBSwitch;    * for future use *
};


#endif
