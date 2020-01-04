Class OpenFSBDebouncer
======================

The OpenFSBDebouncer is debouncing pin input, so one action results in one change event instead of many caused by bouncing contacts. OpenFSBDebouncer is the base class of this library and used in all other classes in this library but can also be used stand-alone. OpenFSBDebouncer can be used in two modes: absolute or relative. In `absolute mode`_ the status is equal to the fysical pin status. This is the technical way. In `relative mode`_ the pin status is compared with the setting ``onState`` to know if the state is `on` or `off`. This is the natural way. Both modes work well and it's up to you which one you prefer to use. If you don't know, use the relative mode to keep things easy. 


Absolute mode methods:

 * fell
 * rose
 * isLow
 * isHigh
 * getValue


Relative mode methods:

 * switchingOn
 * switchingOff
 * isOn
 * isOff

 Relation between ``onState``, the debounced state and the results of the methods:

 +-------------+---------------------+------------------------------+--------------------------------+
 | **onState** | **Debounced state** | **switchingOn()**/**isOn()** | **switchingOff()**/**isOff()** |
 +-------------+---------------------+------------------------------+--------------------------------+
 | ``LOW``     | ``LOW``             | ``true``                     | ``false``                      |
 +-------------+---------------------+------------------------------+--------------------------------+
 | ``LOW``     | ``HIGH``            | ``false``                    | ``true``                       |
 +-------------+---------------------+------------------------------+--------------------------------+
 | ``HIGH``    | ``HIGH``            | ``true``                     | ``false``                      |
 +-------------+---------------------+------------------------------+--------------------------------+
 | ``HIGH``    | ``LOW``             | ``false``                    | ``true``                       |
 +-------------+---------------------+------------------------------+--------------------------------+


You can use a built-in pull-up or pull-down resistor (when supported) to get a stable non-floating `off` state. Pull-up is the default of this class, but you can change this to pull-down when required. The onState used in relative mode is automatically set accordingly. Built-in pull-down resistors are available on MCU's like SAMD, STM32 and ESP32 family MCU's. You can also use an external pull-up/pull-down resistor. In that case you have to set ``EXTERNAL`` mode and the right onState: ``LOW`` or ``HIGH``.



Constructor
-----------
OpenFSBDebouncer( pin )
 Create OpenFSBDebouncer instance with only the mandatory argument ``pin``.
 
 .. function:: OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.

 Defaults:
 
 * mode: ``PULLUP``
 * onState: ``LOW``

 Example:
 
 .. code-block:: c

    OpenFSBDebouncer debouncer( 7 );


OpenFSBDebouncer( pin, mode )
 Create OpenFSBDebouncer instance with custom ``mode``.
 
 .. function:: OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin, uint8_t mode )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.
 * mode: ``PULLUP`` or ``PULLDOWN``. ``EXTERNAL`` is also posible here. In that case ``onState`` is left default (``LOW``). Best way is to specity the onState explicitely when mode is ``EXTERNAL``.

 Defaults:
 
 * onState: ``LOW`` when mode is ``PULLUP`` or ``EXTERNAL``, ``HIGH`` when mode is ``PULLDOWN``

 Example:
 
 .. code-block:: c

    OpenFSBDebouncer debouncer( 7, PULLUP );


OpenFSBDebouncer( pin, mode, onState )
 Create OpenFSBDebouncer instance with custom ``mode`` and ``onState``.
 
 .. function:: OpenFSBDebouncer::OpenFSBDebouncer( uint8_t pin, uint8_t mode, uint8_t onState )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.
 * mode: ``EXTERNAL``. ``PULLUP`` and ``PULLDOWN`` are also possible here, but in that case the value of the onState parameter is ignored and onState will be set automatically according to the mode.
 * onState: the `on` state value ``LOW`` or ``HIGH`` (ignored when mode is ``PULLUP`` or ``PULLDOWN``) 

 Defaults:
 
 * onState: ``LOW`` when mode is ``PULLUP``, ``HIGH`` when mode is ``PULLDOWN``
 
 Example:
 
 .. code-block:: c

    OpenFSBDebouncer debouncer( 7, EXTERNAL, LOW );


Comparison
^^^^^^^^^^
 +---------------------------------------+----------+-------------+-------------------+
 | **Constructor**                       | **mode** | **onState** | **resistor**      |
 +---------------------------------------+----------+-------------+-------------------+
 | OpenFSBDebouncer( 7 )                 | PULLUP   | LOW         | built-in          |
 +---------------------------------------+----------+-------------+-------------------+
 | OpenFSBDebouncer( 7, PULLUP )         | PULLUP   | LOW         | built-in          |
 +---------------------------------------+----------+-------------+-------------------+
 | OpenFSBDebouncer( 7, PULLDOWN )       | PULLDOWN | HIGH        | built-in          |
 +---------------------------------------+----------+-------------+-------------------+
 | OpenFSBDebouncer( 7, EXTERNAL, LOW )  | EXTERNAL | LOW         | external pullup   |
 +---------------------------------------+----------+-------------+-------------------+
 | OpenFSBDebouncer( 7, EXTERNAL, HIGH ) | EXTERNAL | HIGH        | external pulldown |
 +---------------------------------------+----------+-------------+-------------------+





Methods
-------

getOnState()
 Get the actual `on` state value.

 .. function:: uint8_t OpenFSBDebouncer::getOnState()

 Returns: the actual `on` state value ``LOW`` or ``HIGH``.
 
 Example:
 
 .. code-block:: c

     uint8_t val = debouncer.getOnState();



setIntervalMS( intervalMS )
 Set or change the stable interval time.

 .. member:: void OpenFSBDebouncer::setIntervalMS( uint16_t intervalMS )

 Arguments:
 
 * intervalMS: the stable interval time in milliseconds.

 Example:
 
 .. code-block:: c

     debouncer.setIntervalMS( 3 );

 .. note::
   
   The stable interval time is different from some other solutions. This stable interval time is the time to detect the control is not debouncing anymore and starts after the last bounce. Therefore this time should be quite short.


getIntervalMS()
 Get the stable interval time.

 .. function:: uint16_t OpenFSBDebouncer::getIntervalMS()

 Returns: the stable interval time in milliseconds.

 Example:
 
 .. code-block:: c

     uint16_t val = debouncer.getIntervalMS();


getValue()
 Get the debounced pin state.

 .. function:: int OpenFSBDebouncer::getValue()

 Returns: the debounced pin state ``LOW`` or ''HIGH``.
 
 Example:
 
 .. code-block:: c

     int val = debouncer.getValue();


switchingOn()
 Tells if the state is changed from `off` to `on`.

 .. function:: bool OpenFSBDebouncer::switchingOn()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.switchingOn();


switchingOff()
 Tells if the state is changed from `on` to `off`.

 .. function:: bool OpenFSBDebouncer::switchingOff()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.switchingOff();


switching()
 Tells if the state is changed (from `off` to `on` or vice versa).

 .. function:: bool OpenFSBDebouncer::switching()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.switching();


isOn()
 Tells if the state is `on`.

 .. function:: bool OpenFSBDebouncer::isOn()

 Returns: ``true`` if ``onState`` and the debounced state are equal otherwise ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.isOn();


isOff()
 Tells if the state is `off`.

 .. function:: bool OpenFSBDebouncer::isOff()

 Returns: ``true`` if ``onState`` and the debounced state are not equal otherwise ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.isOff();


rose()
 Tells if the debounced state is changed from ``LOW`` to ``HIGH``.

 .. function:: bool OpenFSBDebouncer::rose()

 Returns: ``true`` or ``false``
 
 Example:
 
 .. code-block:: c

     bool val = debouncer.rose();


fell()
  Tells if the debounced state is changed from ``HIGH`` to ``LOW``.

 .. function:: bool OpenFSBDebouncer::fell()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.fell();


isLow()
 Tells if the debounced state is ``LOW``.

 .. function:: bool OpenFSBDebouncer::isLow()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.isLow();


isHigh()
 Tells if the debounced state is ``HIGH``.

 .. function:: bool OpenFSBDebouncer::isHigh()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = debouncer.isHigh();


update()
 Updates the state. This methods should be called before checking the new state. Best way is to include the update in the loop.

 .. function:: void OpenFSBDebouncer::update()

 Example:
 
 .. code-block:: c

     debouncer.update();



Usage
-----

Absolute mode
^^^^^^^^^^^^^
The methods ``fell()`` and ``rose()`` depend on the the (built-in) pull-up or pull-down resistor that is used. Which one indicates the `on` state and the `off` state depends on the used pull-up or pull-down resistor.

When you use a pull-up resistor, you code should be like this:

 .. code-block:: c

    #include <OpenFSBDebouncer.h>

    #define DEBOUNCER_PIN   2

    OpenFSBDebouncer debouncer( DEBOUNCER_PIN ); //  we will use the default mode PULLUP


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      debouncer.update();
      if ( debouncer.fell() ) {
        digitalWrite(LED_BUILTIN, HIGH);  // LED on
      }
      if ( debouncer.rose() ) {
        digitalWrite(LED_BUILTIN, LOW);   // LED off
      }
    }

When you use a pull-down resistor, you have to change ``fell()`` and ``rose()``:

 .. code-block:: c

    #include <OpenFSBDebouncer.h>

    #define DEBOUNCER_PIN   2

    OpenFSBDebouncer debouncer( DEBOUNCER_PIN, PULLDOWN ); //  we will use the built-in pull-down resistor
                                                           //  (only possible when supported by the MCU)

    //OpenFSBDebouncer debouncer( DEBOUNCER_PIN, EXTERNAL, HIGH ); //  otherwise use an external pull-down resistor

    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      debouncer.update();
      if ( debouncer.rose() ) {
        digitalWrite(LED_BUILTIN, HIGH);  // LED on
      }
      if ( debouncer.fell() ) {
        digitalWrite(LED_BUILTIN, LOW);   // LED off
      }
    }



Relative mode
^^^^^^^^^^^^^
The methods ``fell()`` and ``rose()`` depend on the the (built-in) pull-up or pull-down resistor that is used and are technical orientated. In natural language we use `on` and `off` to indicate whether the control makes contact or not. With the relative mode we can program like natural language which can be more clear to understand. Technically it works the same way the absolute mode does, so technically it doesn't matter which one you use. It's your personal preference which one to use. In most cases the relative mode would be the best.

When you use a pull-up resistor your code will look like this:

 .. code-block:: c

    #include <OpenFSBDebouncer.h>

    #define DEBOUNCER_PIN   2

    OpenFSBDebouncer debouncer( DEBOUNCER_PIN ); //  we will use the default mode PULLUP


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      debouncer.update();
      if ( debouncer.switchingOn() ) {
        digitalWrite(LED_BUILTIN, HIGH);  // LED on
      }
      if ( debouncer.switchingOff() ) {
        digitalWrite(LED_BUILTIN, LOW);   // LED off
      }
    }


When you use a pull-down resistor you only have to set a different ``onState``. The rest of the code will be the same:

 .. code-block:: c

    #include <OpenFSBDebouncer.h>

    #define DEBOUNCER_PIN   2

    OpenFSBDebouncer debouncer( DEBOUNCER_PIN, PULLDOWN ); //  we will use the built-in pull-down resistor
                                                           //  (only possible when supported by the MCU)

    //OpenFSBDebouncer debouncer( DEBOUNCER_PIN, EXTERNAL, HIGH ); //  otherwise use an external pull-down resistor


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      debouncer.update();
      if ( debouncer.switchingOn() ) {
        digitalWrite(LED_BUILTIN, HIGH);  // LED on
      }
      if ( debouncer.switchingOff() ) {
        digitalWrite(LED_BUILTIN, LOW);   // LED off
      }
    }
