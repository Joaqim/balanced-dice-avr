#pragma once

#include "common.h"

#ifndef __AVR__
#include <stdlib.h>
#endif

float randfloat(uint16_t seed);
#if 0
uint32_t randint(uint32_t max, uint32_t min = 0);
#endif

uint32_t rand_uint32();
uint16_t rand_uint16();
uint8_t rand_uint8();
uint8_t rand_uint8_range(uint8_t seed, uint8_t max);