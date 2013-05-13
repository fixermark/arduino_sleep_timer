# About

Arduino program for an IR sleep timer for a television.

Listens for an infrared signal to begin sleep countdown. When the signal
is detected, counts down for a fixed amount of time (default is 1/2 hour)
before sending the TV "off" signal via IR.

For more information about how to construct the hardware chassis for this
project, see the following blog entries:
*   [Mounting the controller and IR receiver](http://fixermark.blogspot.com/2013/05/return-of-arduino-part-1-mounting.html)
*   [Mounting indicator LEDs](http://fixermark.blogspot.com/2013/05/return-of-arduino-part-2-status.html)
*   Installing IR transmitter

# Usage

Before installing this program, you may want to modify the following constants in
arduino_sleep_timer.ino:

*   SIGNAL_TO_MATCH: Array representing the IR signal to match to trigger the
    countdown timer.
*   SIGNAL_TO_SEND: The signal to transmit via IR-frequency LED to the
    television.
*   COUNTDOWN_MILLIS: Milliseconds to delay before transmitting the send signal.
*   LEDS[]: Array of pin-outs for the status indicator LEDs (terminated with
    a sentinal value of -1).
*   IR_LISTENER_LED: Signal pin for the PNA4602 IR detector (or its friend,
    the compatible [GP1UX311QS](http://www.adafruit.com/products/157) ).
*   IR_TRANSMITTER_LED: Pin-out for the infrared LED used to transmit
    television remote signal.

Upon installation and power-up, the status indicator lights will blink twice to indicate successful load.
From that point on, sending the relevant SIGNAL_TO_MATCH will start the countdown timer. When the time
expires, SIGNAL_TO_SEND will be transmitted.

If you need to learn the signals for your particular TV and remote combination,
you can readily install the [IR remote signal decoder](https://github.com/fixermark/arduino_remote_signal_decoder)
into the same chassis.

# License

This code is public domain, with no warrantee for fitness for any purpose implied implicitly
or explicitly by its creator.

# Acknowledgements
IR signal listener and transmitter based heavily on Limor's tutorial
(http://www.ladyada.net/learn/sensors/ir.html).
