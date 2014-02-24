#include "sparkle/sparkle.h"

#include <stdlib.h>
#include <util/delay.h>


int main() {
  sparkle_init();

  for (;;) {
    uint8_t i = rand() % SPARKLE_DOT_CNT;

    for (uint8_t h = 0; h < 255; h++) {
      sparkle_dots[i].r = h;
      sparkle_dots[i].g = h;
      sparkle_dots[i].b = h;

      _delay_ms(5);
    }

    for (uint8_t h = 255; h > 0; h--) {
      sparkle_dots[i].r = h;
      sparkle_dots[i].g = h;
      sparkle_dots[i].b = h;

      _delay_ms(5);
    }
  }
}
