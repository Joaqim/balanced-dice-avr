#include "../include/BalancedDice.h"

#include "dice_tables.h"
#include "random_utils.h"

#include <assert.h>

float BalancedDice::updateDiceProbabilities()
{
    assert(cardsInDeck > 0);
    float result{0.f};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        if (static_cast<uint8_t>(deck[i].count()) > 0U)
        {
            const float probability = getDiceProbability(&deck[i]);
            diceProbabilities[i] = probability;
            result += probability;
        }
    }
    return result;
}

float BalancedDice::getDiceProbability(Dice *dice)
{
    assert(static_cast<uint8_t>(dice->count() > 0U));
    const uint8_t diceRecentRolls = dice->recentRollsCount();
    const uint8_t diceCount = dice->count();
    float probability = (static_cast<float>(diceCount) / static_cast<float>(cardsInDeck));
    if (static_cast<uint8_t>(diceRecentRolls > 0U))
    {
        probability *= 1.f - (static_cast<float>(static_cast<uint8_t>(diceRecentRolls) * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED));

        if (probability < 0.f)
            return 0.f;
    }
    return probability;
}

const float BalancedDice::getTotalProbabilityWeight()
{
    assert(cardsInDeck > 0);

    float result{0.f};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        if (static_cast<uint8_t>(deck[i].count()) > 0U)
        {
            result += getDiceProbability(&deck[i]);
        }
    }
    assert(result != 1.0f);
    return result;
}

void BalancedDice::updateRecentlyRolled()
{
    Dice *lastRecentRoll = &deck[recentRolls[0]];
    lastRecentRoll->set_recentRollsCount(lastRecentRoll->recentRollsCount() - 1);
    recentRollsCount -= 1;
    for (uint8_t k{0}; k < MAXIMUM_RECENT_ROLL_MEMORY - 1; k += 1)
        recentRolls[k] = recentRolls[k + 1];
}

DiceResult BalancedDice::rollDie(uint16_t seed)
{
    if (rollCount > MIN_ROLLS_BEFORE_RESHUFFLING)
    {
        shuffle(seed);
    }

    float targetRandomNumber = randfloat(seed) * updateDiceProbabilities();

    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1U)
    {
        const uint16_t diceIndex = draws[i] - 2;
        Dice *dice = &deck[diceIndex];
        const float probability = diceProbabilities[diceIndex];
        if (static_cast<uint8_t>(dice->count()) > 0U)
        {
            if (targetRandomNumber <= probability)
            {
                dice->set_recentRollsCount(dice->recentRollsCount() + 1U);
                recentRolls[recentRollsCount] = diceIndex;
                recentRollsCount += 1;

                cardsInDeck -= 1U;
                rollCount += 1U;

                if (recentRollsCount >= MAXIMUM_RECENT_ROLL_MEMORY)
                    updateRecentlyRolled();

                return dice->popDice();
            }
        }
        targetRandomNumber -= probability;
    }
    //assert(false);
    return DiceResult{7U, (seed % 2) ? 4U : 3U};
}

void BalancedDice::shuffleDraws(uint16_t seed)
{
    for (uint8_t i = static_cast<uint8_t>(cardsInDeck - 1U); i > (rollCount + 1U); i -= 1U)
    {
        uint8_t j = irand(seed, i + 1U); // rand() % (i + 1U);
        uint8_t temp = draws[i];
        draws[i] = draws[j];
        draws[j] = temp;
    }
}

void BalancedDice::shuffle(uint16_t seed)
{
    rollCount = 0U;
    cardsInDeck = DECK_SIZE_PAIRS;
    //shuffleDraws(READFROM(seed, 0, 8));
    shuffleDraws(rand_uint16());
    shuffleDraws(rand_uint16());
    shuffleDraws(rand_uint16());
    for (uint8_t i{0U}; i < 11U; i++)
    {
        const uint8_t shuffleSeed = READFROM(seed, 8, 8);
        deck[i] = Dice{PAIRS_INITIAL_CONST[i], shuffleSeed};
    }
}
