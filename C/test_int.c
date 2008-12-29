#include "wiring.h"
#include <util/delay.h>

int timer = 100;                   // The higher the number, the slower the timing.
int pins[] = { 8, 9, 10, 11, 12 }; // an array of pin numbers
int num_pins = 5;                  // the number of pins (i.e. the length of the array)
int ledPin = 13;   // choose the pin for the LED

// Switch
volatile int state = LOW;      // the current state of the output pin

static void got_interrupt(void)
{ 
    state = HIGH;
}

int main(void)
{
    pinMode(8, OUTPUT);
    attachInterrupt(0, got_interrupt, CHANGE);

    for (;;) {
        if (state == HIGH)
        {
            digitalWrite(8, HIGH);  
        }
        digitalWrite(ledPin, HIGH);   // sets the LED on
        _delay_ms(1000);                  // waits for a second
        digitalWrite(ledPin, LOW);    // sets the LED off
        _delay_ms(1000);                  // waits for a second
    }
    
    return 0;
}
