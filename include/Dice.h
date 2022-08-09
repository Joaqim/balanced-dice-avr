#pragma once
#include "DiceResult.h"

#include "dice_constants.h"

#include "bytes.h"

#include <stdint.h>

struct Dice
{
    uint64_t bits : 64;

    void swap(uint8_t a, uint8_t b, uint8_t size, uint8_t offset = 0);
    void shuffle();

    const bool hasPair(const uint8_t i);
    inline DiceResult popDice(const uint8_t i);

    DiceResult rollDie();

    const bool isEmpty();
    void reset();

    void *pairs;

// 3 bits (0..7) x 12 = 36 byte - Dice Pairs
#if 0
    FIELD(bits, p1d1, 0, 3);
    FIELD(bits, p1d2, 3, 3);
    FIELD(bits, p2d1, 6, 3);
    FIELD(bits, p2d2, 9, 3);
    FIELD(bits, p3d1, 12, 3);
    FIELD(bits, p3d2, 15, 3);
    FIELD(bits, p4d1, 18, 3);
    FIELD(bits, p4d2, 21, 3);
    FIELD(bits, p5d1, 24, 3);
    FIELD(bits, p5d2, 27, 3);
    FIELD(bits, p6d1, 30, 3);
    FIELD(bits, p6d2, 33, 3);
#endif

    // 4 bits (0..15) - Dice Value
    FIELD(bits, value, DICE_VALUE_OFFSET, 4);

#if 0
    // 6 bits - Dice Pairs Available, set bit as boolean in indexed position eq.
    // to dice pair index  (i * 3)
    FIELD(bits, first, 40, 1);
    FIELD(bits, second, 41, 1);
    FIELD(bits, third, 42, 1);
    FIELD(bits, fourth, 43, 1);
    FIELD(bits, fifth, 44, 1);
    FIELD(bits, sixth, 45, 1);
#endif

    // 3 bits (0..7) - Pair Count
    FIELD(bits, count, DICE_PAIRS_COUNT_OFFSET, 3);

    // 15 bits (5 values of 3-bits) - Indices to Pairs, will be shuffled
    FIELD(bits, indices, DICE_INDICES_OFFSET, 15);
};