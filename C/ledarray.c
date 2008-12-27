#include "wiring.h"
#include <avr/io.h>
#include <util/delay.h>

int timer = 100;                   // The higher the number, the slower the timing.
int pins[] = { 2, 3, 4, 5, 6 }; // an array of pin numbers
int num_pins = 5;                  // the number of pins (i.e. the length of the array)
int ledPin = 13;   // choose the pin for the LED

// Switch
int inPin = 10;         // the number of the input pin
int state = LOW;      // the current state of the output pin

int flashleds(void);

int main (void) 
{
  pinMode(inPin, INPUT);  // set inPin as the input
  
  int i;
  for (i = 0; i < num_pins; i++)   // the array elements are numbered from 0 to num_pins - 1
    pinMode(pins[i], OUTPUT);      // set each pin as an output
    
  flashleds(); // Flash once on startup

  while (1) { 
    // Flash LED if button is pushed
    state = digitalRead(inPin);  //
    if (state == LOW) {
      digitalWrite(ledPin, HIGH);  // turn ledPin on to say we have activity
      flashleds();  // Flash the LEDs
    }
    else {
      digitalWrite(ledPin, LOW);  // turn ledPin off to say we are done
    }
  }
  
  return 1;
}


int flashleds(void)
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
  return 1;
}

