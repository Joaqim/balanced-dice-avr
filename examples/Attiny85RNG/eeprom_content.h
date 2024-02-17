#pragma once
#include <avr/pgmspace.h>

#define RNG_MAGIC 0x1D544D50
#define RNG_MAGIC0 0x1D
#define RNG_MAGIC1 0x54
#define RNG_MAGIC2 0x4D
#define RNG_MAGIC3 0x50

#define RNG_MAGIC_ADDRESS 0
#define RNG_CURRENT_ADDRESS 4
#define RNG_READINGS_ADDRESS 5

const uint8_t header[] PROGMEM = {
    RNG_MAGIC0, RNG_MAGIC1, RNG_MAGIC2, RNG_MAGIC3,
    RNG_READINGS_ADDRESS, // current reading
};
