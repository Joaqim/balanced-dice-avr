#pragma once

#ifdef __AVR__
#include <Arduino.h>
#else
#include <stdint.h>
#endif


float randfloat(uint16_t seed);
#if 0
uint32_t randint(uint32_t max, uint32_t min = 0);
#endif
uint8_t irand(uint8_t seed, uint8_t n);


uint32_t rand_uint32();
uint16_t rand_uint16();
uint8_t rand_uint8();