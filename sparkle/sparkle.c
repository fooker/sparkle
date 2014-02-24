#include "sparkle.h"
#include "pwmtable.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile sparkle_color* const sparkle_dots = (sparkle_color[SPARKLE_DOT_CNT]){};


void sparkle_init() {
  // Configure the port as output
  SPARKLE_DDR = (1 << SPARKLE_PIN_R)
              | (1 << SPARKLE_PIN_G)
              | (1 << SPARKLE_PIN_B)
              | (1 << SPARKLE_PIN_CLK)
              | (1 << SPARKLE_PIN_LATCH)
              ;

  // Set initial pin state
  SPARKLE_PORT = (0 << SPARKLE_PIN_R)
               | (0 << SPARKLE_PIN_G)
               | (0 << SPARKLE_PIN_B)
               | (0 << SPARKLE_PIN_CLK)
               | (0 << SPARKLE_PIN_LATCH)
               ;

  // Enable timer
  TCCR0A = (0 << COM0A1)  // OC0A disconnected
         | (0 << COM0A0)  // ...
         | (0 << COM0B1)  // OC0B disconnected
         | (0 << COM0B0)  // ...
         | (0 << WGM01)   // Normal counter
         | (0 << WGM00)   // ...
         ;
  TCCR0B = (0 << FOC0A)   // Disable output compare
         | (0 << FOC0B)   // ...
         | (0 << WGM02)   // Normal counter
         | (0 << CS02)    // Prescaler of 1
         | (0 << CS01)    // resulting ~ 56 hz
         | (1 << CS00)    // @ 14.7456 mhz w/ 1024 steps
         ;
  TIMSK0 = (0 << OCIE0B)  // Disable interrupt on match
         | (0 << OCIE0A)  // ...
         | (1 << TOIE0)   // Enable interrupt on overflow
         ;

  TCNT0 = 0xFF;
  OCR0A = 0xFF;
  OCR0B = 0xFF;

  // Enable interrupts globally
  sei();
}


ISR(TIMER0_OVF_vect) {
  static uint16_t x = 0;

  // Walk over all dots
  for (uint8_t i = 0; i < SPARKLE_DOT_CNT; i++) {
//    register uint8_t p = SPARKLE_PORT
//                       & ~( (1 << SPARKLE_PIN_R)
//                          | (1 << SPARKLE_PIN_G)
//                          | (1 << SPARKLE_PIN_B));

    // Build output with all color bits off assuming clock line and latch line
    // are down before
    register uint8_t p = 0;

    if (x <= pwmtable[sparkle_dots[i].r]) p |= (1 << SPARKLE_PIN_R);
    if (x <= pwmtable[sparkle_dots[i].g]) p |= (1 << SPARKLE_PIN_G);
    if (x <= pwmtable[sparkle_dots[i].b]) p |= (1 << SPARKLE_PIN_B);

    // Load color bits to shift registers
    SPARKLE_PORT = p;

    // Wait for color bits to settle
//    _delay_us(SPARKLE_CLK_DELAY_PRE);

//    // Toggle shift register clock
//    SPARKLE_PORT |= (1 << SPARKLE_PIN_CLK);
//    _delay_us(SPARKLE_CLK_DELAY_HIGH);
//    SPARKLE_PORT &= ~(1 << SPARKLE_PIN_CLK);

    // Wait for shift to settle
//    _delay_us(SPARKLE_CLK_DELAY_POST);
  }

//  // Toggle latch
//  SPARKLE_PORT |= (1 << SPARKLE_PIN_LATCH);
//  _delay_us(SPARKLE_LATCH_DELAY_HIGH);
//  SPARKLE_PORT &= ~(1 << SPARKLE_PIN_LATCH);

  // Go to next PWM step - looping at 1024
  x = (x + 1) % 1024;
}
