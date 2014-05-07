#include "sparkle.h"
#include "pwmtable.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


uint8_t sparkle_dots[3 * 24];


void sparkle_init() {
  // Turn control LED on
  SPARKLE_CTL_DDR |= (1 << SPARKLE_CTL_PIN);
  SPARKLE_CTL_PORT |= (1 << SPARKLE_CTL_PIN);

  // Configure the PWM pins as output
  SPARKLE_PWM_DDR = (1 << SPARKLE_PWM_PIN_OUT)
                  | (1 << SPARKLE_PWM_PIN_CLK)
                  | (1 << SPARKLE_PWM_PIN_LTC)
                  ;

  // Set the PWM pins to defined values
  SPARKLE_PWM_PORT = (0 << SPARKLE_PWM_PIN_OUT)
                   | (0 << SPARKLE_PWM_PIN_CLK)
                   | (0 << SPARKLE_PWM_PIN_LTC)
                   ;

  // Configure the SPI
  SPCR = (1 << SPIE)  // Enable interrupt
       | (1 << SPE)   // Enable SPI
       | (0 << DORD)  // MSB first
       | (1 << MSTR)  // Act as master
       | (0 << CPOL)  // Make SCK low on idle
       | (1 << CPHA)  // Leading edge samples
       | (0 << SPR1)  // Use a pre-scaler of 4
       | (0 << SPR0)
       ;

//  SPSR |= (1 << SPI2X);

  sei();

  SPDR = 0x00;
}

ISR(SPI_STC_vect) {
  static uint8_t step = SPARKLE_PWMTABLE_MAX;

  static uint8_t* dots = &sparkle_dots[0];

  register uint8_t data;
  for (uint8_t i = 0; i < 8; i++) {
    asm volatile ("cp  %1, %2 \n\t"
                  "ror %0     \n\t"
                 :[d] "+r" (data)
                 :[s] "r"  (step),
                  [v] "r"  (*dots++)
                 :);
  }
  SPDR = data;

  // Toggle latch after all registers has been filled
  if (dots == &sparkle_dots[3 * 24]) {
    SPARKLE_PWM_PORT |= (1 << SPARKLE_PWM_PIN_LTC);
    SPARKLE_PWM_PORT &= ~(1 << SPARKLE_PWM_PIN_LTC);

    dots = &sparkle_dots[0];
  }

  // Loop to next step
  if (step == 0) {
    step = SPARKLE_PWMTABLE_MAX;

  } else {
    step--;
  }
}


//  static uint8_t step = 0;
//  static uint8_t byte = 0;
//  static uint8_t data[9] = {};
//
//  if (byte == 0) {
//    // Go to next PWM step - looping at maximum PWM step size
//    step = (step + 1) % 256;
//
//    // Calculate next data
//    data[0] = ((step < sparkle_dots[0][0 + 0]) << 0)
//            | ((step < sparkle_dots[0][0 + 1]) << 1)
//            | ((step < sparkle_dots[0][0 + 2]) << 2)
//            | ((step < sparkle_dots[0][0 + 3]) << 3)
//            | ((step < sparkle_dots[0][0 + 4]) << 4)
//            | ((step < sparkle_dots[0][0 + 5]) << 5)
//            | ((step < sparkle_dots[0][0 + 6]) << 6)
//            | ((step < sparkle_dots[0][0 + 7]) << 7)
//            ;
//    data[1] = ((step < sparkle_dots[0][1 + 0]) << 0)
//            | ((step < sparkle_dots[0][1 + 1]) << 1)
//            | ((step < sparkle_dots[0][1 + 2]) << 2)
//            | ((step < sparkle_dots[0][1 + 3]) << 3)
//            | ((step < sparkle_dots[0][1 + 4]) << 4)
//            | ((step < sparkle_dots[0][1 + 5]) << 5)
//            | ((step < sparkle_dots[0][1 + 6]) << 6)
//            | ((step < sparkle_dots[0][1 + 7]) << 7)
//            ;
//    data[2] = ((step < sparkle_dots[0][2 + 0]) << 0)
//            | ((step < sparkle_dots[0][2 + 1]) << 1)
//            | ((step < sparkle_dots[0][2 + 2]) << 2)
//            | ((step < sparkle_dots[0][2 + 3]) << 3)
//            | ((step < sparkle_dots[0][2 + 4]) << 4)
//            | ((step < sparkle_dots[0][2 + 5]) << 5)
//            | ((step < sparkle_dots[0][2 + 6]) << 6)
//            | ((step < sparkle_dots[0][2 + 7]) << 7)
//            ;
//    data[3] = ((step < sparkle_dots[1][0 + 0]) << 0)
//            | ((step < sparkle_dots[1][0 + 1]) << 1)
//            | ((step < sparkle_dots[1][0 + 2]) << 2)
//            | ((step < sparkle_dots[1][0 + 3]) << 3)
//            | ((step < sparkle_dots[1][0 + 4]) << 4)
//            | ((step < sparkle_dots[1][0 + 5]) << 5)
//            | ((step < sparkle_dots[1][0 + 6]) << 6)
//            | ((step < sparkle_dots[1][0 + 7]) << 7)
//            ;
//    data[4] = ((step < sparkle_dots[1][1 + 0]) << 0)
//            | ((step < sparkle_dots[1][1 + 1]) << 1)
//            | ((step < sparkle_dots[1][1 + 2]) << 2)
//            | ((step < sparkle_dots[1][1 + 3]) << 3)
//            | ((step < sparkle_dots[1][1 + 4]) << 4)
//            | ((step < sparkle_dots[1][1 + 5]) << 5)
//            | ((step < sparkle_dots[1][1 + 6]) << 6)
//            | ((step < sparkle_dots[1][1 + 7]) << 7)
//            ;
//    data[5] = ((step < sparkle_dots[1][2 + 0]) << 0)
//            | ((step < sparkle_dots[1][2 + 1]) << 1)
//            | ((step < sparkle_dots[1][2 + 2]) << 2)
//            | ((step < sparkle_dots[1][2 + 3]) << 3)
//            | ((step < sparkle_dots[1][2 + 4]) << 4)
//            | ((step < sparkle_dots[1][2 + 5]) << 5)
//            | ((step < sparkle_dots[1][2 + 6]) << 6)
//            | ((step < sparkle_dots[1][2 + 7]) << 7)
//            ;
//    data[6] = ((step < sparkle_dots[2][0 + 0]) << 0)
//            | ((step < sparkle_dots[2][0 + 1]) << 1)
//            | ((step < sparkle_dots[2][0 + 2]) << 2)
//            | ((step < sparkle_dots[2][0 + 3]) << 3)
//            | ((step < sparkle_dots[2][0 + 4]) << 4)
//            | ((step < sparkle_dots[2][0 + 5]) << 5)
//            | ((step < sparkle_dots[2][0 + 6]) << 6)
//            | ((step < sparkle_dots[2][0 + 7]) << 7)
//            ;
//    data[7] = ((step < sparkle_dots[2][1 + 0]) << 0)
//            | ((step < sparkle_dots[2][1 + 1]) << 1)
//            | ((step < sparkle_dots[2][1 + 2]) << 2)
//            | ((step < sparkle_dots[2][1 + 3]) << 3)
//            | ((step < sparkle_dots[2][1 + 4]) << 4)
//            | ((step < sparkle_dots[2][1 + 5]) << 5)
//            | ((step < sparkle_dots[2][1 + 6]) << 6)
//            | ((step < sparkle_dots[2][1 + 7]) << 7)
//            ;
//    data[8] = ((step < sparkle_dots[2][2 + 0]) << 0)
//            | ((step < sparkle_dots[2][2 + 1]) << 1)
//            | ((step < sparkle_dots[2][2 + 2]) << 2)
//            | ((step < sparkle_dots[2][2 + 3]) << 3)
//            | ((step < sparkle_dots[2][2 + 4]) << 4)
//            | ((step < sparkle_dots[2][2 + 5]) << 5)
//            | ((step < sparkle_dots[2][2 + 6]) << 6)
//            | ((step < sparkle_dots[2][2 + 7]) << 7)
//            ;
//
//    // Toggle latch
//    SPARKLE_PORT ^= (1 << SPARKLE_PIN_LATCH);
//    SPARKLE_PORT ^= (1 << SPARKLE_PIN_LTC);
//
//    // Begin transmission with first byte
//    byte = 8;
//  }
//
//  // Send next byte
//  SPDR = data[byte--];
//
//  SPDR = 0b10101010;
//}

//void sparkle_update() {
//
//  // Walk over all dots
//  for (uint8_t i = 0; i < SPARKLE_DOT_CNT; i++) {
//
//    // Set output for all color bits while assuming clock line and latch line
//    // are down before
//    SPARKLE_PORT = ((x < sparkle_dots[i].r) << SPARKLE_PIN_R)
//                 | ((x < sparkle_dots[i].g) << SPARKLE_PIN_G)
//                 | ((x < sparkle_dots[i].b) << SPARKLE_PIN_B)
//                 ;
//
//    // Toggle shift register clock
//    SPARKLE_PORT ^= (1 << SPARKLE_PIN_CLK);
//    SPARKLE_PORT ^= (1 << SPARKLE_PIN_CLK);
//  }
//
//  // Toggle latch
//  SPARKLE_PORT ^= (1 << SPARKLE_PIN_LTC);
//  SPARKLE_PORT ^= (1 << SPARKLE_PIN_LTC);
//
//}

void sparkle_set(const uint8_t index,
                 const uint8_t r,
                 const uint8_t g,
                 const uint8_t b) {
  sparkle_dots[0 * 24 + index] = pwmtable[r];
  sparkle_dots[1 * 24 + index] = pwmtable[g];
  sparkle_dots[2 * 24 + index] = pwmtable[b];
}

void sparkle_set_r(const uint8_t index,
                   const uint8_t r) {
  sparkle_dots[0 * 24 + index] = pwmtable[r];
}

void sparkle_set_g(const uint8_t index,
                   const uint8_t g) {
  sparkle_dots[1 * 24 + index] = pwmtable[g];
}

void sparkle_set_b(const uint8_t index,
                   const uint8_t b) {
  sparkle_dots[2 * 24 + index] = pwmtable[b];
}

void sparkle_set_w(const uint8_t index,
                   const uint8_t w) {
  sparkle_dots[0 * 24 + index] = sparkle_dots[1 * 24 + index] = sparkle_dots[2 * 24 + index] = pwmtable[w];
}
