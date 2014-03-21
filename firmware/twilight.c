#include "sparkle/sparkle.h"

#include <stdlib.h>
#include <util/delay.h>

int main() {
  sparkle_init();

  for (;;) {
    uint8_t i = rand() % 8 + 16; // SPARKLE_DOT_CNT;

    for (uint8_t h = 0; h < 0x0F; h++) {
      sparkle_set_w(i,
                    h);

      for (uint16_t x = 0; x < 0xFF; x++)
        sparkle_update();
    }

    for (uint8_t h = 0; h < 0x0F; h++) {
      sparkle_set_w(i,
                    0x0F - h);

      for (uint16_t x = 0; x < 0xFF; x++)
        sparkle_update();
    }

    sparkle_set(i,
                0,
                0,
                0);
    sparkle_update();
    _delay_ms(500);
  }
}
