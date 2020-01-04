Class OpenFSBButton
======================

The OpenFSBButton handles and debounces connected press button pin input. OpenFSBButton can be used in two modes: absolute or relative. In `absolute mode`_ the status is equal to the fysical pin status. This is the technical way. In `relative mode`_ the pin status is compared with the setting ``onState`` to know if the state is `pressed` or `released`. This is the natural way. Both modes work well and it's up to you which one you prefer to use. If you don't know, use the relative mode to keep things easy. 


Absolute mode methods:

 * getValue
 * rose
 * fell
 * isLow
 * isHigh


Relative mode methods:

 * setOnState
 * press();
 * release();
 * isPressed();
 * isReleased();

 Relation between ``onState``, the debounced state and the results of the methods:

 +-------------+---------------------+-----------------------------+--------------------------------+
 | **onState** | **Debounced state** | **press()**/**isPressed()** | **release()**/**isReleased()** |
 +-------------+---------------------+-----------------------------+--------------------------------+
 | ``LOW``     | ``LOW``             | ``true``                    | ``false``                      |
 +-------------+---------------------+-----------------------------+--------------------------------+
 | ``LOW``     | ``HIGH``            | ``false``                   | ``true``                       |
 +-------------+---------------------+-----------------------------+--------------------------------+
 | ``HIGH``    | ``HIGH``            | ``true``                    | ``false``                      |
 +-------------+---------------------+-----------------------------+--------------------------------+
 | ``HIGH``    | ``LOW``             | ``false``                   | ``true``                       |
 +-------------+---------------------+-----------------------------+--------------------------------+


Constructor
-----------
OpenFSBButton( pin )
 Create OpenFSBButton instance with only the mandatory argument ``pin``.
 
 .. function:: OpenFSBButton::OpenFSBButton( uint8_t pin )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.

 Defaults:
 
 * mode: ``PULLUP``
 * onState: ``LOW``

 Example:
 
 .. code-block:: c

    OpenFSBButton debouncer( 7 );


OpenFSBButton( pin, mode )
 Create OpenFSBButton instance with custom ``mode``.
 
 .. function:: OpenFSBButton::OpenFSBButton( uint8_t pin, uint8_t mode )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.
 * mode: ``PULLUP`` or ``PULLDOWN``. ``EXTERNAL`` is also posible here. In that case ``onState`` is left default (``LOW``). Best way is to specity the onState explicitely when mode is ``EXTERNAL``.

 Defaults:
 
 * onState: ``LOW`` when mode is ``PULLUP`` or ``EXTERNAL``, ``HIGH`` when mode is ``PULLDOWN``

 Example:
 
 .. code-block:: c

    OpenFSBButton debouncer( 7, PULLUP );


OpenFSBButton( pin, mode, onState )
 Create OpenFSBButton instance with custom ``mode`` and ``onState``.
 
 .. function:: OpenFSBButton::OpenFSBButton( uint8_t pin, uint8_t mode, uint8_t onState )

 Arguments:
 
 * pin: Pin number the control is connected to. See the board/MCU specifications for the pin numbers.
 * mode: ``EXTERNAL``. ``PULLUP`` and ``PULLDOWN`` are also possible here, but in that case the value of the onState parameter is ignored and onState will be set automatically according to the mode.
 * onState: the `on` state value ``LOW`` or ``HIGH`` (ignored when mode is ``PULLUP`` or ``PULLDOWN``) 

 Defaults:
 
 * onState: ``LOW`` when mode is ``PULLUP``, ``HIGH`` when mode is ``PULLDOWN``
 
 Example:
 
 .. code-block:: c

    OpenFSBButton debouncer( 7, EXTERNAL, LOW );


Comparison
^^^^^^^^^^
 +------------------------------------+----------+-------------+-------------------+
 | **Constructor**                    | **mode** | **onState** | **resistor**      |
 +------------------------------------+----------+-------------+-------------------+
 | OpenFSBButton( 7 )                 | PULLUP   | LOW         | built-in          |
 +------------------------------------+----------+-------------+-------------------+
 | OpenFSBButton( 7, PULLUP )         | PULLUP   | LOW         | built-in          |
 +------------------------------------+----------+-------------+-------------------+
 | OpenFSBButton( 7, PULLDOWN )       | PULLDOWN | HIGH        | built-in          |
 +------------------------------------+----------+-------------+-------------------+
 | OpenFSBButton( 7, EXTERNAL, LOW )  | EXTERNAL | LOW         | external pullup   |
 +------------------------------------+----------+-------------+-------------------+
 | OpenFSBButton( 7, EXTERNAL, HIGH ) | EXTERNAL | HIGH        | external pulldown |
 +------------------------------------+----------+-------------+-------------------+




Methods
-------

getOnState()
 Get the actual `on` ('pressed') state value.

 .. function:: uint8_t OpenFSBButton::getOnState()

 Returns: the actual `on` state value ``LOW`` or ``HIGH``.
 
 Example:
 
 .. code-block:: c

     uint8_t val = button.getOnState();



setIntervalMS( intervalMS )
 Set or change the stable interval time.

 .. function:: void OpenFSBButton::setIntervalMS( uint16_t intervalMS )

 Arguments:
 
 * intervalMS: the stable interval time in milliseconds.

 Example:
 
 .. code-block:: c

     button.setIntervalMS( 3 );

 .. note::
   
   The stable interval time is different from some other solutions. This stable interval time is the time to detect the control is not debouncing anymore and starts after the last bounce. Therefore this time should be quite short.


getIntervalMS()
 Get the stable interval time.

 .. function:: uint16_t getIntervalMS()

 Returns: the stable interval time in milliseconds.

 Example:
 
 .. code-block:: c

     uint16_t val = button.getIntervalMS();


getValue()
 Get the debounced pin state.

 .. function:: int getValue()

 Returns: the debounced pin state ``LOW`` or ''HIGH``.
 
 Example:
 
 .. code-block:: c

     int val = button.getValue();


press()
 Tells if the state is changed from `released' to `pressed`.

 .. function:: bool press()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = button.press();


release()
 Tells if the state is changed from `pressed` to `released`.

 .. function:: bool release()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = button.release();


isPressed()
 Tells if the state is `pressed`.

 .. function:: bool isPressed()

 Returns: ``true`` if ``onState`` and the debounced state are equal otherwise ``false``

 Example:
 
 .. code-block:: c

     bool val = button.isPressed();


isReleased()
 Tells if the state is `released`.

 .. function:: bool isReleased()

 Returns: ``true`` if ``onState`` and the debounced state are not equal otherwise ``false``

 Example:
 
 .. code-block:: c

     bool val button.isReleased();


rose()
 Tells if the debounced state is changed from ``LOW`` to ``HIGH``.

 .. function:: bool rose()

 Returns: ``true`` or ``false``
 
 Example:
 
 .. code-block:: c

     bool val = button.rose();


fell()
  Tells if the debounced state is changed from ``HIGH`` to ``LOW``.

 .. function:: bool fell()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = button.fell();


isLow()
 Tells if the debounced state is ``LOW``.

 .. function:: bool isLow()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = button.isLow();


isHigh()
 Tells if the debounced state is ``HIGH``.

 .. function:: bool isHigh()

 Returns: ``true`` or ``false``

 Example:
 
 .. code-block:: c

     bool val = button.isHigh();


update()
 Updates the state. This methods should be called before checking the new state. Best way is to include the update in the loop.

 .. function:: void update()

 Example:
 
 .. code-block:: c

     button.update();



Usage
-----

Absolute mode
^^^^^^^^^^^^^
The methods ``fell()`` and ``rose()`` depend on the the (build-in) pull-up or pull-down resistor that we use. Which one indicates the `pressed` state and the `released` state depends on using a pull-up or pull-down resistor.

When you use a pull-up resistor, you code should be like this:

 .. code-block:: c

    #include <OpenFSBbutton.h>

    #define BUTTON_PIN   2

    OpenFSBButton button( BUTTON_PIN );


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      button.update();
      if ( button.fell() ) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      if ( button.rose() ) {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

When you use a pull-down resistor, you have to change ``fell()`` and ``rose()``:

 .. code-block:: c

    #include <OpenFSBbutton.h>

    #define BUTTON_PIN   2

    OpenFSBbutton button( DEBOUNCER_PIN, PULLDOWN );         //  we will use the built-in pull-down resistor
                                                             //  (only possible when supported by the MCU)

    //OpenFSBbutton button( DEBOUNCER_PIN, EXTERNAL, HIGH ); //  otherwise use an external pull-down resistor


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      button.update();
      if ( button.rose() ) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      if ( button.fell() ) {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }


Relative mode
^^^^^^^^^^^^^
The methods ``fell()`` and ``rose()`` depend on the the (build-in) pull-up or pull-down resistor that we use and are technical orientated. In natural language we use `pressed` and `released` to indicate whether the control makes contact or not. With the relative mode we can program like natural language which can be more clear to understand. In relative mode the code is more self-documenting. Technically it works the same way the absolute mode does, so technically it doesn't matter which one you use. It's your personal preference which one to use.

When you use a pull-up resistor your code will look like this:

 .. code-block:: c

    #include <OpenFSBbutton.h>

    #define BUTTON_PIN   2

    OpenFSBbutton button( BUTTON_PIN ); //  we will use the default onState: LOW


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      button.update();
      if ( button.press() ) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      if ( button.release() ) {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }


When you use a pull-down resistor you only have to set a different ``onState``. The rest of the code will be the same:

 .. code-block:: c

    #include <OpenFSBbutton.h>

    #define BUTTON_PIN   2

    OpenFSBbutton button( DEBOUNCER_PIN, PULLDOWN );         //  we will use the built-in pull-down resistor
                                                             //  (only possible when supported by the MCU)

    //OpenFSBbutton button( DEBOUNCER_PIN, EXTERNAL, HIGH ); //  otherwise use an external pull-down resistor


    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }


    void loop() {
      button.update();
      if ( button.press() ) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      if ( button.release() ) {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

