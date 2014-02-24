#ifndef SPARKLE_CONFIG_H_
#define SPARKLE_CONFIG_H_


/**
 * The number of dots available.
 */
#ifndef SPARKLE_DOT_CNT
#define SPARKLE_DOT_CNT 1
#endif

/**
 * The port to use.
 *
 * The port requires at least 5 free / usable pins. The first 3 pins are used to
 * control the red / green / blue channels (see {@link SPARKLE_PIN_R},
 * {@link SPARKLE_PIN_G}, {@link SPARKLE_PIN_B}). The 4th pin is used as a
 * common clock for the channels shift registers (see {@link SPARKLE_PIN_CLK})
 * and the 5th pin is used as a common latch (see {@link SPARKLE_PIN_LATCH}).
 */
#ifndef SPARKLE_PORT
#define SPARKLE_PORT PORTC
#endif

/**
 * The DDR to use to configure the {@link SPARKLE_PORT}.
 *
 * The configured DDR must match the configured port.
 */
#ifndef SPARKLE_DDR
#define SPARKLE_DDR DDRC
#endif

/**
 * The pin number to transmit the red channel.
 */
#ifndef SPARKLE_PIN_R
#define SPARKLE_PIN_R PC1
#endif

/**
 * The pin number to transmit the green channel.
 */
#ifndef SPARKLE_PIN_G
#define SPARKLE_PIN_G PC2
#endif

/**
 * The pin number to transmit the blue channel.
 */
#ifndef SPARKLE_PIN_B
#define SPARKLE_PIN_B PC3
#endif

/**
 * The pin number to control the clock.
 *
 * All color channels are using a common clock line.
 */
#ifndef SPARKLE_PIN_CLK
#define SPARKLE_PIN_CLK PC4
#endif

/**
 * The pin number to control the latch.
 *
 * All color channels are using a common latch line.
 */
#ifndef SPARKLE_PIN_LATCH
#define SPARKLE_PIN_LATCH PC5
#endif

/**
 * The number of us to wait for the values to settle.
 *
 * The delay is applied after setting the values for the channels and before
 * setting the clock line to HIGH.
 */
#ifndef SPARKLE_CLK_DELAY_PRE
#define SPARKLE_CLK_DELAY_PRE 10
#endif

/**
 * The number of us to keep the clock line HIGH.
 *
 * The delay is applies after setting the clock line to HIGH and before setting
 * the click line to LOW.
 */
#ifndef SPARKLE_CLK_DELAY_HIGH
#define SPARKLE_CLK_DELAY_HIGH 20
#endif

/**
 * The number of us to wait for the shift registers to process the values.
 *
 * The delay is applied after setting the clock line to LOW and before setting
 * new values for the channels.
 */
#ifndef SPARKLE_CLK_DELAY_POST
#define SPARKLE_CLK_DELAY_POST 10
#endif

/**
 * The number of us to keep the latch line HIGH.
 *
 * The delay is applies after setting the latch line to HIGH and before setting
 * the latch line to LOW.
 */
#ifndef SPARKLE_LATCH_DELAY_HIGH
#define SPARKLE_LATCH_DELAY_HIGH 20
#endif

#endif /* SPARKLE_CONFIG_H_ */
