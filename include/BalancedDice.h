#pragma once
#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"
#include "deck_defines.h"

#include <stdint.h>

class BalancedDice
{
public:
    BalancedDice(uint16_t seed): recentRollsCount{0} {
        shuffle(seed);
    }

    float getDiceProbability(Dice *dice);
    const inline float getTotalProbabilityWeight();

    float updateDiceProbabilities();
    void updateRecentlyRolled();

    DiceResult rollDie(uint16_t seed);

    void shuffleDraws(uint16_t seed);
    void shuffle(uint16_t seed);

    Dice deck[DECK_SIZE];

    uint8_t cardsInDeck : 6; // 0..63

    uint8_t draws[DECK_SIZE_PAIRS] = INITIAL_DRAWS;

    uint8_t rollCount : 5; // 0..31

    float diceProbabilities[11];

    uint8_t recentRolls[MAXIMUM_RECENT_ROLL_MEMORY] = {0U};
    uint8_t recentRollsCount: 4;
};
