#pragma once

#ifdef __AVR__
#include <Arduino.h>
#include <stdint.h>
typedef unsigned int size_t;
#else
#include <stddef.h>
#include <stdint.h>
#endif

