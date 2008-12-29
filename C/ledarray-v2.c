#include "wiring.h"
#include <avr/io.h>
#include <util/delay.h>

int timer = 100;                   // The higher the number, the slower the timing.
int pins[] = { 8, 9, 10, 11, 12 }; // an array of pin numbers
int num_pins = 5;                  // the number of pins (i.e. the length of the array)

// Switch
int state = 1;      // the current state of the LED loop.
volatile int change_state = LOW; // Has the interrupt been activated

int leds_off(void);
int leds_on(void);
int leds_blink(void);
int leds_flash(void);
int change_mode(void);
void got_interrupt(void);

int main (void) 
{
  init();  // Arduino Init
    
  attachInterrupt(0, got_interrupt, RISING);  // Attach got_interrupt() to interrupt 0 (pin2)

  int i;
  for (i = 0; i < num_pins; i++)   // the array elements are numbered from 0 to num_pins - 1
    pinMode(pins[i], OUTPUT);      // set each pin as an output
    
  leds_flash(); // Flash once on startup

  while (1) { 
    
    // If change_state has been activated by got_interrupt() change the LED mode
    if (change_state == HIGH) {
      change_mode();
      change_state = LOW;  // Set it back to LOW
    }   

    // Do the correct LED trick according to our mode
    switch (state) {
    case 0:
      leds_off();
      break;
    case 1:
      leds_on();
      break;
    case 2:
      leds_blink();
      break;
    case 3:
      leds_flash();
      break;
    }
  }
  
  return 0;
}

void got_interrupt(void)
{
  change_state = HIGH;  // Set change_state so we change_mode() next loop.
}


int change_mode(void)
{
  // Cycle the modes
  if (state == 3) 
    state = 0;
  else
    state++;

  return 0;
}

int leds_off(void) 
{
  int i;
  for(i = 0; i < num_pins; i++) 
    digitalWrite(pins[i], LOW);

  _delay_ms(timer);

  return 0;
}

int leds_on(void) 
{
  int i;
  for(i = 0; i < num_pins; i++) 
    digitalWrite(pins[i], HIGH);

  _delay_ms(timer);

  return 0;
}

int leds_blink(void)
{
  int i;
  for(i = 0; i < num_pins; i++) 
    digitalWrite(pins[i], HIGH);
  _delay_ms(timer * 2);
  for(i = 0; i < num_pins; i++) 
    digitalWrite(pins[i], LOW);
  _delay_ms(timer * 2);

  return 0;
}

int leds_flash(void)
{
  int i;
  for (i = 0; i < num_pins; i++) { // loop through each pin...
    digitalWrite(pins[i], HIGH);   // turning it on,
    _delay_ms(timer);                  // pausing,
    digitalWrite(pins[i], LOW);    // and turning it off.
  }
  // And again in reverse
  for (i = num_pins - 1; i >= 0; i--) { 
    digitalWrite(pins[i], HIGH);
    _delay_ms(timer);
    digitalWrite(pins[i], LOW);
  }
  return 0;
}

