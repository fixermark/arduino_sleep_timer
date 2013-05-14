// Arduino sleep timer, by Mark T. Tomczak
// (iam@fixermark.com).
// Public domain, released without warranty
// for fitness for use in any purpose.
//
// Master driving program for Arduino sleep timer.
// Overall process:
// * Listen for SIGNAL_TO_MATCH from the IR sensor.
// * When the signal is seen, wait for COUNTDOWN_MILLIS
// * At end of wait, send SIGNAL_TO_SEND via IR transmitter.

#include "remote_codes.h"

// Countdown time, in milliseconds
// 30 minutes. For some reason, the compiler
// doesn't handle (1000 * 60 * 30) correctly,
// resolving it to 30528
#define COUNTDOWN_MILLIS 1800000
// Cycle time for flashing lights
#define FLASH_LIGHT_DELAY_MILLIS 250
// Number of times to flash lights
#define FLASH_LIGHT_COUNT 2

// Signal to listen for that activates the sleep timer.
// This should be a signal that doesn't normally do anything
// to the TV.
#define SIGNAL_TO_MATCH CODE_PHILIPS_BLUE
// Signal to send to the TV to turn it off.
#define SIGNAL_TO_SEND CODE_PHILIPS_POWER

// Pin-outs for the status LEDs. -1 acts
// as an end-of-array indicator.
int LEDS[] = {
  11, 10, 9, 6, -1
};

// Pin of the signal IR detector.
int IR_LISTENER_LED = 2;

// Pin-out of the infrared LED, used to
// send remote control signals to the television.
int IR_TRANSMITTER_LED = 13;

void setup()   {       
  Serial.begin(9600);
  // Set up our libraries
  SetupLedControl(LEDS);
  SetupSignalListener(IR_LISTENER_LED);
  SetupTransmitter(IR_TRANSMITTER_LED);
  
  // Flash the lights to let user know that the
  // sleep timer is ready to listen.
  FlashLights(3, 100);
}

void loop() {
 // We're listening for hte designated signal to
 // indicate we should start the sleep timer.
 Serial.println("Listening for IR signal");
  uint16_t test[200];
  int count;
  count = listenForIR(test, 200);
  Serial.println("Test hears");
  uint16_t *test2 = test;
  while (test2[1] != 0) { 
    Serial.print(*test2, DEC);
    Serial.print(" ");
    Serial.println(test2[1], DEC);
    test2 += 2;
  }
  Serial.print(*test2, DEC);
  Serial.print(" ");
  Serial.println(test2[1], DEC);

  if (CompareSignals(test, count, SIGNAL_TO_MATCH)) {
    Serial.println("Matching signal detected");

    // Flash lights to let user know that we saw the signal.
    FlashLights(FLASH_LIGHT_COUNT, FLASH_LIGHT_DELAY_MILLIS);
    Serial.print("Asking for countdown of ");
    Serial.print(COUNTDOWN_MILLIS, DEC);
    Serial.print("\n");

    // Run the countdown while updating the lights to indicate
    // time remaining approaching 0. This won't return until
    // the countdown is over.    
    CountDown(COUNTDOWN_MILLIS);
    
    // Send the code to turn off the TV.
    SendCode(SIGNAL_TO_SEND);
  }
  // ... and we'll loop around, back to listening for a trigger
  // signal.
}
