#pragma once
#include <Arduino.h>

float randfloat(uint16_t seed);
#if 0
uint32_t randint(uint32_t max, uint32_t min = 0);
#endif
uint8_t irand(uint8_t seed, uint8_t n);
