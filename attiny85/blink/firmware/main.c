/*
    Blinks LED on pin 4.
    (This way I can keep the ISP pins connected for testing)
*/

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB = (1 << DDB4);

    for (;;) {
        _delay_ms(500);

        PORTB ^= (1 << PB4);
    }

    return 0;   /* never reached */
}
