#pragma once
#include <stdlib.h>

typedef unsigned int size_t;

// TODO: Cast index to correct type to avoid narrowing warnings


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

#include <assert.h>

static inline uint32_t swapBits(uint32_t bits, const uint8_t a, const uint8_t b, const uint8_t size, const uint8_t offset = 0)
{
    uint8_t temp = READFROM(bits, a * size + offset, size);
    assert(temp > 0);
    WRITETO(bits, a * size + offset, size,
            READFROM(bits, b * size + offset, size));
    WRITETO(bits, b * size + offset, size, temp);
    return bits;
}

static inline uint32_t shuffleBits(uint8_t seed,uint32_t bits, const uint8_t len ,const uint8_t size, const uint8_t offset = 0)
{
    for (uint8_t i{static_cast<uint8_t>(len - 1)}; i > 0; i -= 1)
    {
        uint8_t j = seed % (i + 1);
        swapBits(bits,i, j, size, offset);
    }
    return bits;
}