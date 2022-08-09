#pragma once
#include <stdlib.h>

typedef unsigned int size_t;

#define GETMASK(index, size) ((((size_t)1 << (size)) - 1) << (index))
#define READFROM(data, index, size) \
    (((data)&GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value)               \
    ((data) = (((data) & (~GETMASK((index), (size)))) | \
               (((value) << (index)) & (GETMASK((index), (size))))))
#define FIELD(data, name, index, size)                                         \
    inline decltype(data) name() const { return READFROM(data, index, size); } \
    inline void set_##name(decltype(data) value)                               \
    {                                                                          \
        WRITETO(data, index, size, value);                                     \
    }

#define FIELD_BOOL(data, name, index)                                 \
    inline bool name() const { return READFROM(data, index, 1) > 0; } \
    inline void set_##name(uint8_t value) { WRITETO(data, index, 1, value); }

#define BitSet(bit, bitPosition) ((bit) |= (0x01 << (bitPosition)))

#define BitClear(bit, bitPosition) ((bit) &= ~(0x01 << (bitPosition)))

#define BitRead(bit, bitPosition) (((bit) >> bitPosition) & 0x01)

#define BitWrite(bit, bitPosition, value) \
    ((value) == 0x01 ? BitSet(bit, bitPosition) : BitClear(bit, bitPosition))

#define Bit(bitPosition) (1 << (bitPosition))
