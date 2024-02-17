#pragma once
#include "common.h"

#define GETMASK(index, size) ((size >= sizeof(uint8_t) * 8) ? 0 : ((((uint8_t)1 << (size)) - 1) << (static_cast<uint8_t>(index))))
#define READFROM(data, index, size) \
    (((data) & GETMASK((static_cast<uint8_t>(index)), (size))) >> (static_cast<uint8_t>(index)))
