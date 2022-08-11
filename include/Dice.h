#pragma once
#include "DiceResult.h"

#include "dice_constants.h"

#include "bytes.h"

#include <stdint.h>

struct Dice
{
    uint32_t bits : 23;

    void swap(uint8_t a, uint8_t b, uint8_t size, uint8_t offset = 0);
    void shuffle(uint8_t seed);

    const bool hasPair(const uint8_t i);
    DiceResult popDice();

    const bool isEmpty();
    void reset();

    void *pairs;

    // 3 bits (0..7) - Pair Count
    FIELD(bits, count, 0, 3);

    // 3 bits (0..7) x 6 = 16 byte - Dice Pairs
    //FIELD(bits, pairs, 1, 16);
#if 0
    FIELD(bits, p1d1, 1, 3);
    FIELD(bits, p2d1, 4, 3);
    FIELD(bits, p3d1, 7, 3);
    FIELD(bits, p4d1, 10, 3);
    FIELD(bits, p5d1, 13, 3);
    FIELD(bits, p6d1, 16, 3);
#endif
    // 2 bits (0..3) - Roll Count
    FIELD(bits, roll_count, DICE_ROLL_COUNT_OFFSET, 2);

    // 4 bits (0..15) - Dice Value
    FIELD(bits, value, DICE_VALUE_OFFSET, 4);
};