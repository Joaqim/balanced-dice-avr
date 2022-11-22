#include "../include/BalancedDice.h"

#include "random_utils.h"

#include <assert.h>

float BalancedDice::updateDiceProbabilities()
{
    assert(cardsInDeck > 0U);
    float result{0.f};
    for (uint8_t i{0}; i < DECK_SIZE; i += 1U)
    {
        const float probability = getDiceProbability(&deck[i]);
        diceProbabilities[i] = probability;
        result += probability;
    }
    return result;
}

float BalancedDice::getDiceProbability(Dice *dice)
{
    if (dice->isEmpty())
    {
        return 0.f;
    }

    const uint8_t diceRecentRolls = dice->rollCount();
    const uint8_t diceCount = dice->count();

    float probability = static_cast<float>(diceCount) / static_cast<float>(cardsInDeck);
    if (diceRecentRolls > 0U)
    {
        probability *= 1.f - (static_cast<float>(diceRecentRolls) * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED);

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
        if (deck[i].hasPairs())
        {
            result += getDiceProbability(&deck[i]);
        }
    }
    assert(result != 1.0f);
    return result;
}

void BalancedDice::shiftRecentlyRolled()
{
    Dice *lastRecentRoll = &deck[recentRolls[0]];
    lastRecentRoll->decreaseRollCount();
    for (uint8_t k{0U}; k < MAXIMUM_RECENT_ROLL_MEMORY - 1U; k += 1U)
        recentRolls[k] = recentRolls[k + 1U];
    recentRollsCount -= 1U;
}

DiceResult BalancedDice::popDie(Dice *dice, uint16_t diceIndex)
{
    if (recentRollsCount >= MAXIMUM_RECENT_ROLL_MEMORY)
    {
        shiftRecentlyRolled();
    }

    dice->setRollCount(dice->rollCount() + 1U);
    recentRolls[recentRollsCount] = diceIndex;

    cardsInDeck -= 1U;
    rollCount += 1U;

    recentRollsCount += 1U;

    return dice->popDice();
}

DiceResult BalancedDice::rollDie(uint32_t seed)
{
    if (cardsInDeck <= MINIMUM_CARDS_LEFT_BEFORE_RESHUFFLING)
    {
        shuffle(seed);
    }

    float targetRandomNumber = randfloat(seed) * updateDiceProbabilities();

#ifdef USE_ORDERED_DRAWS
    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1U)
    {
        const uint16_t diceIndex = draws[i] - 2U;
        Dice *dice = &deck[diceIndex];
        const float probability = diceProbabilities[diceIndex];
        {
            if (targetRandomNumber <= probability && probability > 0.f)
                return popDie(dice, diceIndex);
        }
        targetRandomNumber -= probability;
    }
    // TODO: Debug why it inevitably reaches this point.
    // assert(false);
    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1U)
    {
        const uint16_t diceIndex = draws[i] - 2U;

        Dice *dice = &deck[diceIndex];
        if (dice->hasPairs())
        {
            return popDie(&deck[diceIndex], diceIndex);
        }
    }

    assert(false);
#else
    while (true)
    {
        const uint16_t diceIndex = rand_uint8() % 11U;
        const float probability = diceProbabilities[diceIndex];
        if (targetRandomNumber <= probability)
        {
            Dice *dice = &deck[diceIndex];
            if(dice->hasPairs())
                return popDie(dice, diceIndex);
        }
        //diceProbabilities[diceIndex] += deck[diceIndex].count() / cardsInDeck;
        targetRandomNumber -= probability;
    }

#endif
    // return DiceResult{7U, (seed % 2) ? 4U : 3U};
}

#ifdef USE_ORDERED_DRAWS

#define USE_MACRO_SHUFFLE

#ifdef USE_MACRO_SHUFFLE
#include "shuffle_macro.h"
decl_shuffle(uint8_t)
#endif

    void BalancedDice::shuffleDraws(uint32_t seed)
{
#ifdef USE_MACRO_SHUFFLE
    shuffle_uint8_t(draws, 36, seed);
#else
    for (uint8_t i = static_cast<uint8_t>(cardsInDeck - 1U); i > (rollCount + 1U); i -= 1U)
    {
        uint8_t j = rand_uint8_range(seed, i + 1U); // rand() % (i + 1U);
        uint8_t temp = draws[i];
        draws[i] = draws[j];
        draws[j] = temp;
    }
#endif
}
#endif

void BalancedDice::shuffle(uint32_t seed)
{
    rollCount = 0U;
    cardsInDeck = DECK_SIZE_PAIRS;

#ifdef USE_ORDERED_DRAWS
    shuffleDraws(READFROM(seed, 0, 16));
#endif

    const uint8_t shuffleSeed = READFROM(seed, 16, 8);
    for (uint8_t i{0U}; i < 11U; i++)
    {
        deck[i] = Dice{PAIRS_INITIAL_CONST[i], shuffleSeed};
    }
}
