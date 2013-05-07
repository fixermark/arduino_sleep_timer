// Control LED firing patterns
// -1 used as sentinel value
int *g_led_control_leds;
int g_led_control_num_leds = 0;

// *leds is the arraay of LED pin IDs, terminated with a sentinel value of -1.
void SetupLedControl(int *leds) {
  g_led_control_leds = leds;
  g_led_control_num_leds = 0;
  while(*leds != -1) {
    g_led_control_num_leds++;
    pinMode(*leds, OUTPUT);
    leds++;     
  }
}

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

void CountDown(int time_to_countdown_millis) {
  unsigned long start_time = millis();
  // TODO(mtomczak): account for rollover after 50 days. You should probably build
  // a timer library with some structs to hold that state.

  for(
    int time_elapsed = 0;
    time_elapsed < time_to_countdown_millis;
    time_elapsed = (int)(millis() - start_time)) {
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
      if (i==0) {
        Serial.println(output);
      }
      
      analogWrite(g_led_control_leds[i], output);
    }    
  }
}
