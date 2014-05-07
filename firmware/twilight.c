#include "sparkle/sparkle.h"

#include <stdlib.h>
#include <util/delay.h>

int main() {
  sparkle_init();

  for (;;) {

    for (uint8_t h = 0; h < 0x0F; h++) {
      for (uint8_t i = 0; i < 0x0F; i++) {
        sparkle_set_r(i,
                      h);
      }
      _delay_ms(5);
    }

//    uint8_t i = rand() % 24; // SPARKLE_DOT_CNT;
//
//    for (uint8_t h = 0; h < 0x0F; h++) {
//      sparkle_set_w(i,
//                    h);
//
//      _delay_ms(5);
//    }
//
//    for (uint8_t h = 0; h < 0x0F; h++) {
//      sparkle_set_w(i,
//                    0x0F - h);
//
//      _delay_ms(5);
//    }
//
//    sparkle_set(i,
//                0,
//                0,
//                0);
//    _delay_ms(500);
  }
}
