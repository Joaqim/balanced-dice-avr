#pragma once
#include "DiceResult.h"
#include "dice_constants.h"

#include "common.h"

struct Dice
{
    Dice(uint8_t diceValue_, uint8_t shuffleSeed = 0U) : diceValue(diceValue_)
    {
        initializePairs();

        if (shuffleSeed != 0U)
        {
            shuffle(shuffleSeed);
        }
    }

    void initializePairs();

    inline void decreaseRollCount() { rollCount -= 1; }
    inline void increaseRollCount() { rollCount += 1; }

    void shuffle(uint8_t seed);

    uint8_t getPair(uint8_t count);
    DiceResult popDice();

    inline const bool hasPairs() { return pairCount > 0U; }
    void reset(uint8_t shuffleSeed);

    uint8_t pairCount;
    uint8_t pairs[6];

    uint8_t rollCount = 0;
    const uint8_t diceValue;
};