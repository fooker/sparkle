#ifndef SPARKLE_PWMTABLE_H_
#define SPARKLE_PWMTABLE_H_

#include <avr/pgmspace.h>

/**
 * The size of the PWM table.
 */
#define SPARKLE_PWMTABLE_SIZE 16

/**
 * The maximum value in the PWM table.
 */
#define SPARKLE_PWMTABLE_MAX 256

static const uint8_t pwmtable[SPARKLE_PWMTABLE_SIZE] = { 0,
                                                         1,
                                                         2,
                                                         3,
                                                         5,
                                                         7,
                                                         11,
                                                         15,
                                                         22,
                                                         31,
                                                         45,
                                                         63,
                                                         90,
                                                         127,
                                                         180,
                                                         254 };

#endif /* SPARKLE_PWMTABLE_H_ */
