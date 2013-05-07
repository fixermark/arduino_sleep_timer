#include "remote_codes.h"

// Countdown time, in milliseconds
#define COUNTDOWN_MILLIS (1000 * 60 * 30)
// Cycle time for flashing lights
#define FLASH_LIGHT_DELAY_MILLIS 250
// Number of times to flash lights
#define FLASH_LIGHT_COUNT 2

#define SIGNAL_TO_MATCH CODE_PHILIPS_BLUE
#define SIGNAL_TO_SEND CODE_PHILIPS_POWER

int LEDS[] = {
  11, 10, 9, 6, -1
};

int IR_LED = 13;

void setup()   {                
  Serial.begin(9600);
  SetupLedControl(LEDS);
  SetupTransmitter(IR_LED);
  
  FlashLights(3, 100);
}

void loop() {
 Serial.println("Listening for IR signal");
  uint16_t test[200];
  int count;
  count = listenForIR(test, 200);
  if (CompareSignals(test, count, SIGNAL_TO_MATCH)) {
    Serial.println("Blue detected");
    FlashLights(FLASH_LIGHT_COUNT, FLASH_LIGHT_DELAY_MILLIS);
    CountDown(COUNTDOWN_MILLIS);
    SendCode(SIGNAL_TO_SEND);
  }
}
