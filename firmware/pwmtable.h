#ifndef SPARKLE_PWMTABLE_H_
#define SPARKLE_PWMTABLE_H_

/**
 * The size of the PWM table.
 */
#define SPARKLE_PWMTABLE_SIZE 64

/**
 * The maximum value in the PWM table.
 */
#define SPARKLE_PWMTABLE_MAX 255

/**
 * The PWM table.
 *
 * The table maps the linear value to a brightness value reflecting the eyes
 * perception of brightness.
 */
static const uint8_t pwmtable[SPARKLE_PWMTABLE_SIZE] = { 0,
                                                         1,
                                                         1,
                                                         1,
                                                         2,
                                                         2,
                                                         2,
                                                         2,
                                                         2,
                                                         2,
                                                         3,
                                                         3,
                                                         3,
                                                         3,
                                                         4,
                                                         4,
                                                         4,
                                                         5,
                                                         5,
                                                         6,
                                                         6,
                                                         7,
                                                         7,
                                                         8,
                                                         9,
                                                         9,
                                                         10,
                                                         11,
                                                         12,
                                                         13,
                                                         15,
                                                         16,
                                                         17,
                                                         19,
                                                         21,
                                                         23,
                                                         25,
                                                         27,
                                                         29,
                                                         32,
                                                         35,
                                                         38,
                                                         41,
                                                         45,
                                                         49,
                                                         54,
                                                         59,
                                                         64,
                                                         70,
                                                         76,
                                                         83,
                                                         90,
                                                         98,
                                                         107,
                                                         117,
                                                         128,
                                                         139,
                                                         152,
                                                         165,
                                                         180,
                                                         197,
                                                         214,
                                                         234,
                                                         255 };

#endif /* SPARKLE_PWMTABLE_H_ */
