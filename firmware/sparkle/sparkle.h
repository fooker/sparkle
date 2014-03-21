#ifndef SPARKLE_H_
#define SPARKLE_H_

#include <stdint.h>
#include <avr/io.h>

#include "../config.h"

/**
 * Initialize the controller.
 */
void sparkle_init();

void sparkle_update();

void sparkle_set(const uint8_t index,
                 const uint8_t r,
                 const uint8_t g,
                 const uint8_t b);

void sparkle_set_r(const uint8_t index,
                   const uint8_t r);

void sparkle_set_g(const uint8_t index,
                   const uint8_t g);

void sparkle_set_b(const uint8_t index,
                   const uint8_t b);

void sparkle_set_w(const uint8_t index,
                   const uint8_t w);

#endif /* SPARKLE_H_ */
