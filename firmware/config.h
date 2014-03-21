#ifndef SPARKLE_CONFIG_H_
#define SPARKLE_CONFIG_H_


/**
 * The number of dots available.
 */
#ifndef SPARKLE_DOT_CNT
#define SPARKLE_DOT_CNT 24
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
#define SPARKLE_PIN_R PC0
#endif

/**
 * The pin number to transmit the green channel.
 */
#ifndef SPARKLE_PIN_G
#define SPARKLE_PIN_G PC1
#endif

/**
 * The pin number to transmit the blue channel.
 */
#ifndef SPARKLE_PIN_B
#define SPARKLE_PIN_B PC2
#endif

/**
 * The pin number to control the clock.
 *
 * All color channels are using a common clock line.
 */
#ifndef SPARKLE_PIN_CLK
#define SPARKLE_PIN_CLK PC3
#endif

/**
 * The pin number to control the latch.
 *
 * All color channels are using a common latch line.
 */
#ifndef SPARKLE_PIN_LATCH
#define SPARKLE_PIN_LATCH PC4
#endif

#endif /* SPARKLE_CONFIG_H_ */
