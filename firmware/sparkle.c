#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>

#include "config.h"
#include "pwmtable.h"


/**
 * The storage for current values of the dots.
 *
 * The layout for this is:
 *   dots[bank][port]
 */
uint8_t sparkle_dots[SPARKLE_PINS_COUNT];


/**
 * The main function.
 */
int main() {
  // Turn control LED on
  SPARKLE_CTL_DDR  |= (1 << SPARKLE_CTL_PIN);
  SPARKLE_CTL_PORT |= (1 << SPARKLE_CTL_PIN);

  // Configure the PWM pins as output
  SPARKLE_SPI_DDR = (1 << SPARKLE_SPI_PIN_OUT)
                  | (1 << SPARKLE_SPI_PIN_CLK)
                  | (1 << SPARKLE_SPI_PIN_LTC)
                  ;

  // Set the PWM pins to defined values
  SPARKLE_SPI_PORT = (0 << SPARKLE_SPI_PIN_OUT)
                   | (0 << SPARKLE_SPI_PIN_CLK)
                   | (0 << SPARKLE_SPI_PIN_LTC)
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

//  SPSR |= (1 << SPI2X); // Run at double speed

  // Configure the TWI
//  TWAR = (SPARKLE_TWI_ADDRESS << 1)
//       | (0 << TWGCE) // Do not react on general calls
//       ;
//  TWCR = (1 << TWEN)  // Enable TWI
//       | (1 << TWIE)  // Enable interrupts
//       | (1 << TWINT) // ...
//       | (0 << TWEA)  // Clear acknowledge flag
//       | (0 << TWSTA) // ... start flag
//       | (0 << TWSTO) // ... and stop flag
//       ;

  sparkle_dots[0 * SPARKLE_PINS_PORTS + 0] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 0] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 0] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 1] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 1] = 64;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 1] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 2] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 2] = 128;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 2] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 3] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 3] = 192;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 3] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 4] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 4] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 4] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 5] = 192;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 5] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 5] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 6] = 128;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 6] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 6] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 7] = 64;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 7] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 7] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 8] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 8] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 8] = 0;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 9] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 9] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 9] = 64;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 10] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 10] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 10] = 128;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 11] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 11] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 11] = 192;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 12] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 12] = 255;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 12] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 13] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 13] = 192;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 13] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 14] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 14] = 128;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 14] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 15] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 15] = 64;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 15] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 16] = 0;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 16] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 16] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 17] = 64;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 17] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 17] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 18] = 128;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 18] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 18] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 19] = 192;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 19] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 19] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 20] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 20] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 20] = 255;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 21] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 21] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 21] = 192;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 22] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 22] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 22] = 128;
  sparkle_dots[0 * SPARKLE_PINS_PORTS + 23] = 255;
  sparkle_dots[1 * SPARKLE_PINS_PORTS + 23] = 0;
  sparkle_dots[2 * SPARKLE_PINS_PORTS + 23] = 64;

  // Enable interrupts
//  sei();

  // Send a dummy value to trigger setting of SPI transmission completed flag
  SPDR = 0b10101010;

  // Main loop
  for (;;) {

    // Loop over all steps
    for (uint8_t step = 0;
         step < SPARKLE_PWMTABLE_MAX;
         step++) {

      // Loop of all dots
      uint8_t* dots = sparkle_dots;
      while (dots != sparkle_dots + SPARKLE_PINS_COUNT) {

        // Build data block for 8 dots each
        register uint8_t data;
        for (uint8_t j = 0; j < 8; j++) {
          asm volatile ("cp  %1, %2 \n\t"
                        "ror %0     \n\t"
                       :[d] "+r" (data)
                       :[s] "r"  (step),
                        [v] "r"  (*(dots++))
                       :);
        }

        // Wait until SPI transmission completed flag is set for previous block
        while(!(SPSR & (1 << SPIF)));

        // Send data block to SPI
        SPDR = data;
      }

      // Toggle latch after all registers has been filled
      SPARKLE_SPI_PORT |=  (1 << SPARKLE_SPI_PIN_LTC);
      SPARKLE_SPI_PORT &= ~(1 << SPARKLE_SPI_PIN_LTC);
    }
  }

  return 0;
}

//ISR(TWI_vect) {
//  static uint8_t idx = 0xFF;
//  static uint8_t bnk = 0;
//
//  switch (TWSR & 0b11111100) {
//  case 0x60: // RX Address received
//    idx = 0xFF;
//    bnk = 0;
//    break;
//
//  case 0x80: // RX Data received - ACK
//  case 0x88: // RX Data received - NACK
//    if (idx == 0xFF) {
//      idx = TWDR;
//      bnk = 0;
//
//    } else {
//      sparkle_dots[bnk++ * SPARKLE_PINS_PORTS + idx] = pwmtable[TWDR % SPARKLE_PWMTABLE_SIZE];
//
//      if (bnk == SPARKLE_PINS_BANKS) {
//        bnk = 0;
//        idx++;
//      }
//    }
//
//    break;
//
//  default:
//    break;
//  }
//
//  TWSR |= (1 << TWINT);
//}
