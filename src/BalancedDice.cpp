#include "../include/BalancedDice.h"

#include "dice_tables.h"
#include "shuffle_macro.h"
#include "random_utils.h"

#include <assert.h>

decl_shuffle(Dice);
decl_shuffle(uint8_t);

float BalancedDice::getDiceProbability(Dice *dice)
{
    assert(dice->count() > 0);
    const float probabilityModifier = 1 - (dice->roll_count() * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED);
    const float probability = dice_probability_lookup_table[rollCount][dice->count() - 1] * probabilityModifier;
    if (probability < 1)
        return 0;
    return probability;
}

const float BalancedDice::getTotalProbabilityWeight()
{
    float result{0};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        Dice *dice = &deck[i];
        if (dice->count() > 0)
        {
            result += getDiceProbability(dice);
        }
    }
    return result;
}

DiceResult BalancedDice::rollDie(uint16_t seed)
{
    if (rollCount > MIN_ROLLS_BEFORE_RESHUFFLING)
    {
        shuffle(seed);
    }

    const float totalProbability = getTotalProbabilityWeight();

    float targetRandomNumber = randfloat(seed) * totalProbability;

    Dice *dice;
    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1)
    {
        assert(i < 15);
        dice = &deck[draws[i]];
        if (dice->count() > 0)
        {
            const float probability = getDiceProbability(dice);
            if (targetRandomNumber <= probability)
            {
                cardsInDeck -= 1;
                rollCount += 1;
                return dice->popDice();
            }
            targetRandomNumber -= probability;
        }
    }
    assert(false);
    return DiceResult{0, 0};
}

void BalancedDice::shuffle(uint16_t seed)
{
    rollCount = 0;
    cardsInDeck = DECK_SIZE_PAIRS;
    shuffle_uint8_t(draws, DECK_SIZE_PAIRS, READFROM(seed, 0, 8));
    for (uint8_t i{0}; i < 11; i++)
    {
        deck[i].reset();
        deck[i].shuffle(READFROM(seed, 8, 16));
    }
}
