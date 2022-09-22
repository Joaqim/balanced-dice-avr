#include "../include/BalancedDice.h"

#include "dice_tables.h"
#include "random_utils.h"

#include <assert.h>

float BalancedDice::getDiceProbability(Dice *dice)
{
    assert(static_cast<uint8_t>(dice->count() > 0U));
    const float probabilityModifier = 1 - (static_cast<uint8_t>(dice->roll_count()) * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED);
#if 1
    assert(rollCount <= MIN_ROLLS_BEFORE_RESHUFFLING);
    const float probability = dice_probability_lookup_table[rollCount][dice->count() - 1] * probabilityModifier;
#else
    const float probability = (dice->count() / cardsInDeck) * probabilityModifier;
#endif
    if (probability < 1)
        return 0;
    return probability;
}

const float BalancedDice::getTotalProbabilityWeight()
{
    float result{0.f};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        uint8_t diceCount = static_cast<uint8_t>(deck[i].count());
        if (diceCount > 0U)
        {
            result += diceCount / cardsInDeck; // getDiceProbability(dice);
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

    float targetRandomNumber = randfloat(seed) * getTotalProbabilityWeight();

    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1)
    {
        // 2022-09-21: What is this supposed to catch?
        // assert(i < 13);
        Dice *dice = &deck[draws[i] - 2];
        if (static_cast<uint8_t>(dice->count()) > 0)
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
    return DiceResult{0U, 0U};
}

void BalancedDice::shuffleDraws()
{
    for (uint8_t i = static_cast<uint8_t>(cardsInDeck - 1); i > (rollCount + 1); i -= 1)
    {
        uint8_t j = rand() % (i + 1);
        uint8_t temp = draws[i];
        draws[i] = draws[j];
        draws[j] = temp;
    }
}

void BalancedDice::shuffle(uint16_t seed)
{
    rollCount = 0;
    cardsInDeck = DECK_SIZE_PAIRS;
    shuffleDraws();
    for (uint8_t i{0}; i < 11; i++)
    {
        const uint8_t shuffleSeed = static_cast<uint8_t>(READFROM(seed, 8, 8));
        deck[i] = Dice{PAIRS_INITIAL_CONST[i], shuffleSeed};
    }
}
