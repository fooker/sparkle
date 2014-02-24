#ifndef SPARKLE_H_
#define SPARKLE_H_

#include <stdint.h>
#include <avr/io.h>

#include "../config.h"


typedef volatile struct {
  volatile uint8_t r;
  volatile uint8_t g;
  volatile uint8_t b;
} sparkle_color;


/**
 * Initialize the controller.
 */
void sparkle_init();


/**
 * The colors of the dots.
 */
extern volatile sparkle_color* const sparkle_dots;

#endif /* SPARKLE_H_ */
