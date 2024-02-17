#pragma once
#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"
#include "deck_defines.h"

#include "common.h"

class BalancedDice
{
public:
// cppcheck-suppress uninitMemberVar
    explicit BalancedDice(uint32_t seed) {
        init(seed);
    }

    BalancedDice() {}

    float getDiceProbability(Dice *dice);
    const inline void init(uint32_t seed) { shuffle(seed); };
    const inline float getTotalProbabilityWeight();

    float updateDiceProbabilities();
    void shiftRecentlyRolled();

    DiceResult rollDie(uint32_t seed);

    void shuffle(uint32_t seed);

    Dice deck[DECK_SIZE] = INITIAL_DECK;

    uint8_t cardsInDeck : 6; // 0..63

    uint8_t rollCount : 5; // 0..31

    float diceProbabilities[11];

    uint8_t recentRolls[MAXIMUM_RECENT_ROLL_MEMORY] = {0U};
    uint8_t recentRollsCount : 4;

private:
    DiceResult popDie(Dice *dice, uint16_t diceIndex);
};
