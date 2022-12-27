#pragma once
#include "common.h"

// TODO: Cast index to correct type to avoid narrowing warnings
#define GETMASK(index, size) ((((size_t)1 << (size)) - 1) << (index))
#define READFROM(data, index, size) \
    (((data)&GETMASK((index), (size))) >> (index))
