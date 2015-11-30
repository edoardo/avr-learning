/*
    Toggle on and off a LED on pin 4 every second
    (This way I can keep the ISP pins connected for testing)
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int counter;

int main(void) {
    // set pin 4 as output
    DDRB |= (1 << DDB4);

    // disable global interrupts
    cli();

    // reset TCCR1
    TCCR1 = 0;

    // set compare match register to 244 (for 1/2 sec. timeout @ 8 MHz and 16384 prescaler)
    OCR1A = 244;

    // set prescaler to 16384
    TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10);

    // enable timer output compare interrupt
    TIMSK |= (1 << OCIE1A);

    // enable interrupts
    sei();

    while (1) {}
}

// called every 0.5 seconds
ISR(TIMER1_COMPA_vect) {
    counter++;

    // 1 second elapsed
    if (counter == 2) {
        // toggle pin 4 value
        PORTB ^= (1 << PB4);

        // reset counter
        counter = 0;
    }
}
