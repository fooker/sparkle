#ifndef SPARKLE_CONFIG_H_
#define SPARKLE_CONFIG_H_

/**
 * The number of LEDs to control
 */
#define SPARKLE_PINS_PORTS 24

/**
 * The number of banks.
 * Each LED is attached to the same pin on each bank for each LED channel.
 */
#define SPARKLE_PINS_BANKS 3

/**
 * The number of pins over all banks.
 */
#define SPARKLE_PINS_COUNT (( SPARKLE_PINS_PORTS * SPARKLE_PINS_BANKS ))

/**
 * The number of register chips required for all LEDs.
 */
#define SPARKLE_PINS_CHIPS (( ceil(SPARKLE_PINS_COUNT / 8) ))

/**
 * The SPI port register.
 */
#define SPARKLE_SPI_PORT PORTB

/**
 * The SPI data direction register.
 */
#define SPARKLE_SPI_DDR DDRB

/**
 * The SPI latch pin.
 */
#define SPARKLE_SPI_PIN_LTC PB2

/**
 * The SPI clock pin.
 */
#define SPARKLE_SPI_PIN_CLK PB5

/**
 * The SPI data pin.
 */
#define SPARKLE_SPI_PIN_OUT PB3

/**
 * The control LED port register.
 */
#define SPARKLE_CTL_PORT PORTD

/**
 * The control LED data direction register.
 */
#define SPARKLE_CTL_DDR DDRD

/**
 * The control LED pin.
 */
#define SPARKLE_CTL_PIN PD1

/**
 * The TWI address.
 */
#define SPARKLE_TWI_ADDRESS 0x60

#endif /* SPARKLE_CONFIG_H_ */
