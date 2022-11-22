#pragma once
#include "DiceResult.h"

#include "dice_constants.h"

#include "bytes.h"

#include <stdint.h>

struct Dice
{
    uint32_t bits : 28;
    Dice() : bits(0){};
    Dice(uint32_t bits_, uint8_t shuffleSeed = 0U) : bits(bits_)
    {
        if (shuffleSeed != 0U)
        {
            shuffle(shuffleSeed);
        }
    };
    void swap(uint8_t a, uint8_t b, uint8_t size, uint8_t offset = 0);
    void shuffle(uint8_t seed);

    // const bool hasPair(const uint8_t i);
    uint8_t getPair(uint8_t count);
    DiceResult popDice();

    inline const bool isEmpty() { return count() == 0U; }
    inline const bool hasPairs() { return count() > 0U; }
    void reset();

    void *pairs;

    // 3 bits (0..7) - Pair Count
    FIELD(bits, count, 0, 3);

    // 3 bits (0..7) x 6 = 16 byte - Dice Pairs
    // FIELD(bits, pairs, 1, 16);
#if 0
    FIELD(bits, p1d1, 3, 3);
    FIELD(bits, p2d1, 6, 3);
    FIELD(bits, p3d1, 9, 3);
    FIELD(bits, p4d1, 12, 3);
    FIELD(bits, p5d1, 15, 3);
    FIELD(bits, p6d1, 18, 3);
#endif
    // 3 bits (0..7) - Roll Count
    inline uint8_t rollCount() const { return READFROM(bits, DICE_ROLL_COUNT_OFFSET, 3); }
    inline void setRollCount(uint8_t value) { WRITETO(bits, DICE_ROLL_COUNT_OFFSET, 3, value); }
    inline void decreaseRollCount() { setRollCount(static_cast<uint8_t>(rollCount()) - 1U); }

    // 4 bits (0..15) - Dice Value
    inline uint8_t diceValue() const { return READFROM(bits, DICE_VALUE_OFFSET, 4); }
    inline void setDiceValue(uint8_t value) { WRITETO(bits, DICE_VALUE_OFFSET, 4, value); }
};