#include "wiring.h"
#include <avr/io.h>
#include <util/delay.h>

int timer = 100;                   // The higher the number, the slower the timing.
int pins[] = { 8, 9, 10, 11, 12 }; // an array of pin numbers
int num_pins = 5;                  // the number of pins (i.e. the length of the array)
int ledPin = 13;   // choose the pin for the LED

// Switch
int state = 1;      // the current state of the output pin
volatile int change_state = LOW;

int leds_off(void);
int leds_on(void);
int leds_blink(void);
int leds_flash(void);
int change_mode(void);
void got_interrupt(void);

int main (void) 
{
  attachInterrupt(0, got_interrupt, CHANGE);

  int i;
  for (i = 0; i < num_pins; i++)   // the array elements are numbered from 0 to num_pins - 1
    pinMode(pins[i], OUTPUT);      // set each pin as an output
    
  leds_flash(); // Flash once on startup

  while (1) { 

    if (change_state == HIGH) {
      change_mode();
      change_state = LOW;
    }   

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
  change_state = HIGH;
}


int change_mode(void)
{
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

