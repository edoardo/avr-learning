/* Name: main.c
 * Author: Edoardo Sabadelli
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

void setup_watchdog();
void flash_led();

volatile int wdi_counter;

int main(void) {
    // LED on pin 4
    DDRB = (1 << DDB4);

    // power down mode
    // the watchdog interrupt wakes up the MCU
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    setup_watchdog();

    for (;;) {
        // put MCU in sleep mode (sleep_enable(), sleep_cpu(), sleep_disable())
        sleep_mode();

        // MCU is sleeping...

        // WDT interrupt wakes MCU
        // and execution resumes here
        // blink LED every 3 seconds
        if (wdi_counter == 3) {
            flash_led();

            // reset wdi_counter
            wdi_counter = 0;
        }

        // when loop starts over, MCU is put to sleep again
    }

    return 0;
}

void flash_led() {
    // toggle LED on pin 4
    PORTB ^= (1 << PB4);

    _delay_ms(250);

    PORTB ^= (1 << PB4);
}

void setup_watchdog() {
    // disable global interrupts
    cli();

    // clear watchdog reset flag
    MCUSR &= ~(1 << WDRF);

    // start timed sequence
    WDTCR |= (1 << WDCE) | (1 << WDE);

    // enable watchdog timeout interrupt (WDIE)
    // set watchdog timer prescaler (1 sec.)
    WDTCR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);

    // enable interrupts
    sei();
}

// called every 1 second
ISR(WDT_vect) {
    wdi_counter++;
}
