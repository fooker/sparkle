#include "sparkle.h"
#include "pwmtable.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef volatile struct {
  volatile uint8_t r;
  volatile uint8_t g;
  volatile uint8_t b;
} sparkle_color;

volatile sparkle_color* const sparkle_dots = (sparkle_color[SPARKLE_DOT_CNT] ) { };

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
}

void sparkle_update() {
  static uint16_t x = 0;

  // Walk over all dots
  for (uint8_t i = 0; i < SPARKLE_DOT_CNT; i++) {

    // Set output for all color bits while assuming clock line and latch line
    // are down before
    SPARKLE_PORT = ((x < sparkle_dots[i].r) << SPARKLE_PIN_R)
                 | ((x < sparkle_dots[i].g) << SPARKLE_PIN_G)
                 | ((x < sparkle_dots[i].b) << SPARKLE_PIN_B)
                 ;

    // Toggle shift register clock
    SPARKLE_PORT ^= (1 << SPARKLE_PIN_CLK);
    SPARKLE_PORT ^= (1 << SPARKLE_PIN_CLK);
  }

  // Toggle latch
  SPARKLE_PORT ^= (1 << SPARKLE_PIN_LATCH);
  SPARKLE_PORT ^= (1 << SPARKLE_PIN_LATCH);

  // Go to next PWM step - looping at maximum PWM step size
  x = (x + 1) % 256;
}

void sparkle_set(const uint8_t index,
                 const uint8_t r,
                 const uint8_t g,
                 const uint8_t b) {
  sparkle_dots[index].r = pwmtable[r];
  sparkle_dots[index].g = pwmtable[g];
  sparkle_dots[index].b = pwmtable[b];
}

void sparkle_set_r(const uint8_t index,
                   const uint8_t r) {
  sparkle_dots[index].r = pwmtable[r];
}

void sparkle_set_g(const uint8_t index,
                   const uint8_t g) {
  sparkle_dots[index].g = pwmtable[g];
}

void sparkle_set_b(const uint8_t index,
                   const uint8_t b) {
  sparkle_dots[index].b = pwmtable[b];
}

void sparkle_set_w(const uint8_t index,
                   const uint8_t w) {
  sparkle_dots[index].r = sparkle_dots[index].g = sparkle_dots[index].b = pwmtable[w];
}
