#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

#include "config.h"
#include "pwmtable.h"



#define sbi(reg, bit) ((reg) |=  (1 << (bit)))
#define cbi(reg, bit) ((reg) &= ~(1 << (bit)))



/**
 * The storage for current values of the dots.
 *
 * The layout for this is:
 *   dots[bank][port]
 */
volatile uint8_t sparkle_dots[SPARKLE_PINS_BANKS][SPARKLE_PINS_CHANS];



/**
 * The main function.
 */
int main() {
  // Configure the control LED
  sbi(SPARKLE_CTL_DDR, SPARKLE_CTL_PIN);
  cbi(SPARKLE_CTL_PORT, SPARKLE_CTL_PIN);

  // Configure the SPI pins
  sbi(SPARKLE_SPI_DDR, SPARKLE_SPI_PIN_OUT);
  sbi(SPARKLE_SPI_DDR, SPARKLE_SPI_PIN_CLK);
  sbi(SPARKLE_SPI_DDR, SPARKLE_SPI_PIN_LTC);


  // Set the SPI pins to defined values
  cbi(SPARKLE_SPI_PORT, SPARKLE_SPI_PIN_OUT);
  cbi(SPARKLE_SPI_PORT, SPARKLE_SPI_PIN_CLK);
  cbi(SPARKLE_SPI_PORT, SPARKLE_SPI_PIN_LTC);

  // Configure the SPI
  sbi(SPCR, MSTR);  // Act as master

  cbi(SPCR, CPOL);  // Make SCK low on idle
  sbi(SPCR, CPHA);  // Leading edge samples

  sbi(SPCR, DORD);  // MSB last

  cbi(SPCR, SPR1);  // Use a pre-scaler of 16
  cbi(SPCR, SPR0);  // ...
  sbi(SPSR, SPI2X); // Run at double speed

  cbi(SPCR, SPIE);  // Disable SPI interrupts

  sbi(SPCR, SPE);   // Enable SPI

  // Configure the TWI
  TWAR = SPARKLE_TWI_ADDRESS << 1;

  cbi(TWAR, TWGCE); // Do not react on general calls

  sbi(TWCR, TWEA);  // Set acknowledge flag

  cbi(TWCR, TWSTA); // Clear start
  cbi(TWCR, TWSTO); // ... and stop flags

  sbi(TWCR, TWIE);  // Enable interrupts

  sbi(TWCR, TWEN);  // Enable TWI

  // Wipe the the dots values
  for (uint8_t i = 0; i < 24; i++) {
    sparkle_dots[0][i] = pwmtable[0];
    sparkle_dots[1][i] = pwmtable[0];
    sparkle_dots[2][i] = pwmtable[0];
  }

  // Enable interrupts
  sei();

  // Turn control LED on
  sbi(SPARKLE_CTL_PORT, SPARKLE_CTL_PIN);

  // Send a dummy value to trigger setting of SPI transmission completed flag
  SPDR = 0b11111111;

  // Main loop
  uint8_t step = 0;
  for (;;) {
    for (uint8_t i = 0; i < SPARKLE_PINS_BANKS; i++) {
      for (uint8_t j = 0; j < SPARKLE_PINS_PORTS; j++) {
        register uint8_t data = 0;

        for (uint8_t k = 0; k < 8; k++) {
          asm volatile ("cp %1, %2 \n\t ror %0"
                        : "+r" (data)
                        : "r" (step),
                          "r" (sparkle_dots[i][j * 8 + k]));
        }

        while(!(SPSR & (1 << SPIF)));
        SPDR = data;

        asm volatile ("nop");
        asm volatile ("nop");
      }
    }

//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[0][ 0 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[0][ 8 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[0][16 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[1][ 0 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[1][ 8 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[1][16 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[2][ 0 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[2][ 8 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;
//    for (uint8_t i = 0; i < 8; i++) { asm volatile ("cp %1, %2 \n\t ror %0" : "+r" (data) : "0" (data), "r" (step), "r" (sparkle_dots[2][16 + i])); } while(!(SPSR & (1 << SPIF))); SPDR = data;

    // Toggle latch after all registers has been filled
    sbi(SPARKLE_SPI_PORT, SPARKLE_SPI_PIN_LTC);
    cbi(SPARKLE_SPI_PORT, SPARKLE_SPI_PIN_LTC);

    // Move to the next step - looping at 255 using overflow
    step++;
  }

  return 0;
}

static uint8_t idx = 0xFF;
static uint8_t bnk = 0x00;

ISR(TWI_vect) {

  switch (TW_STATUS) {
  case TW_SR_SLA_ACK: // RX address received
    idx = 0xFF;
    bnk = 0x00;

    TWCR = (1 << TWEN)
         | (1 << TWIE)
         | (1 << TWINT)
         | (1 << TWEA)
         | (0 << TWSTA)
         | (0 << TWSTO)
         | (0 << TWWC)
         ;
    break;

  case TW_SR_DATA_ACK: // RX data received - ACK
    if (idx == 0xFF) {
      idx = TWDR;
      bnk = 0x00;

    } else {
      sparkle_dots[bnk++][idx] = pwmtable[TWDR];

      if (bnk == SPARKLE_PINS_BANKS) {
        bnk = 0;
        idx++;
      }
    }

    TWCR = (1 << TWEN)
         | (1 << TWIE)
         | (1 << TWINT)
         | (1 << TWEA)
         | (0 << TWSTA)
         | (0 << TWSTO)
         | (0 << TWWC)
         ;
    break;

  default:
    TWCR = (1 << TWEN)
         | (1 << TWIE)
         | (1 << TWINT)
         | (1 << TWEA)
         | (0 << TWSTA)
         | (0 << TWSTO)
         | (0 << TWWC)
         ;
    break;
  }
}
