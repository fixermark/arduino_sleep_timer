// LED control library, by Mark T. Tomczak 
// (iam@fixermark.com).
// Public domain, released without warranty
// for fitness for use in any purpose.
// To use:
// * Call SetupLedControl with an array of LED inputs IDs
//   (-1 terminates the array as a sentinel value)
// * Call functions in the library to control the LEDs.

// Control LED firing patterns
// -1 used as sentinel value
int *g_led_control_leds;
int g_led_control_num_leds = 0;

// *leds is the arraay of LED pin IDs, 
// terminated with a sentinel value of -1. All other functions
// in this library affect these LEDs.
void SetupLedControl(int *leds) {
  g_led_control_leds = leds;
  g_led_control_num_leds = 0;
  while(*leds != -1) {
    g_led_control_num_leds++;
    pinMode(*leds, OUTPUT);
    leds++;     
  }
}

// Flash the lights "times" times, with a delay of
// flash_delay_millis milleseconds between each on-off
// pulse (so we take 2 * flash_delay_millis to flash one time).
//
// Note: Since we used delay here, not millis(), this isn't
//  an extremely accurate timer; it will take slightly longer than
//  times * 2 * flash_delay_millis to evaluate.
void FlashLights(int times, int flash_delay_millis) {
  for(int i=0; i < times; i++) {
    for(int i=0; i < g_led_control_num_leds; i++) {
      analogWrite(g_led_control_leds[i], 255);
    }
    delay(flash_delay_millis);
    for(int i=0; i < g_led_control_num_leds; i++) {
      analogWrite(g_led_control_leds[i], 0);
    }
    delay(flash_delay_millis);   
  }
}

// Wait for time_to_countdown_millis. As we wait,
// slowly dim the lights, one by one, to indicate how much
// time remains.
void CountDown(long time_to_countdown_millis) {
  Serial.println(time_to_countdown_millis, DEC);
  unsigned long start_time = millis();
  // TODO(mtomczak): account for rollover after 50 days. You should probably build
  // a timer library with some structs to hold that state.

  for(
    long time_elapsed = 0;
    time_elapsed < time_to_countdown_millis;
    time_elapsed = (long)(millis() - start_time)) {
    float percent_remaining = (float)(time_to_countdown_millis - time_elapsed) / (float)(time_to_countdown_millis);
    float led_fraction = 1.0 / (float)(g_led_control_num_leds);
    for (int i=0; i < g_led_control_num_leds; i++) {
      int output = 255;
      if (percent_remaining < led_fraction * (float)(i + 1)) {
        if (percent_remaining < led_fraction * (float)(i)) {
          output = 0;
        } else { // percent remaining is in range led_fraction * (i, i+1)
          output = (int)((percent_remaining - (led_fraction * (float)(i))) * 255.0 / led_fraction);
        }
      }   
      
      analogWrite(g_led_control_leds[i], output);
    }    
  }
}
