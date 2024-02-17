#include "../include/BalancedDice.h"

#include "random_utils.h"
#include "byte_utils.h"

#include <assert.h>

/**
 * Updates the probabilities of each dice in the deck.
 *
 * @return The total probability of all dice in the deck.
 */
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

/**
 * Calculate the probability of getting a pair with the given Dice object.
 *
 * @param dice pointer to the Dice object
 *
 * @return the probability of getting the value of dice in current deck
 *
 * @throws None
 */
float BalancedDice::getDiceProbability(Dice *dice)
{
    if (!dice->hasPairs())
    {
        return 0.f;
    }

    const uint8_t diceRecentRolls = dice->rollCount;
    const uint8_t pairCount = dice->pairCount;

    float probability = static_cast<float>(pairCount) / static_cast<float>(cardsInDeck);
    if (diceRecentRolls > 0U)
    {
        probability *= 1.f - (static_cast<float>(diceRecentRolls) * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED);

        if (probability < 0.f)
            return 0.f;
    }
    return probability;
}

/**
 * Calculate the total probability weight of the dice in the deck.
 *
 * @return the total probability weight
 *
 * @throws Assertion error if cardsInDeck is not greater than 0
 */
const float BalancedDice::getTotalProbabilityWeight()
{
    assert(cardsInDeck > 0);

    float result{0.f};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        result += getDiceProbability(&deck[i]);
    }
    assert(result != 1.0f);
    return result;
}

/**
 * Shifts the recently rolled dice in the BalancedDice deck.
 */
void BalancedDice::shiftRecentlyRolled()
{
    Dice *lastRecentRoll = &deck[recentRolls[0]];
    lastRecentRoll->decreaseRollCount();
    for (uint8_t k{0U}; k < MAXIMUM_RECENT_ROLL_MEMORY - 1U; k += 1U)
        recentRolls[k] = recentRolls[k + 1U];
    recentRollsCount -= 1U;
}

/**
 * Pop a die from the Dice object and update the recent rolls and roll counts.
 *
 * @param dice The Dice object from which to pop the die.
 * @param diceIndex The index of the die to pop.
 *
 * @return The result of two thrown dice from  of the popped dice pair.
 *
 * @throws None
 */
DiceResult BalancedDice::popDie(Dice *dice, uint16_t diceIndex)
{
    if (recentRollsCount >= MAXIMUM_RECENT_ROLL_MEMORY)
    {
        shiftRecentlyRolled();
    }

    dice->increaseRollCount();
    recentRolls[recentRollsCount] = diceIndex;

    cardsInDeck -= 1U;
    rollCount += 1U;

    recentRollsCount += 1U;

    return dice->popDice();
}

/**
 * Rolls a balanced dice based on the given seed.
 *
 * @param seed the seed for random number generation
 *
 * @return the result of the dice roll
 *
 * @throws None
 */
DiceResult BalancedDice::rollDie(uint32_t seed)
{
    if (cardsInDeck <= MINIMUM_CARDS_LEFT_BEFORE_RESHUFFLING)
    {
        shuffle(seed);
    }

    float targetRandomNumber = randfloat(seed) * updateDiceProbabilities();

    while (true)
    {
        const uint8_t diceIndex = rand_uint8() % 11U;
        const float probability = diceProbabilities[diceIndex];
        if (targetRandomNumber <= probability)
        {
            Dice *dice = &deck[diceIndex];
            if (dice->hasPairs())
                return popDie(dice, diceIndex);
        }
        targetRandomNumber -= probability;
    }
    return DiceResult{7U, static_cast<uint8_t>((seed % 2) ? 4U : 3U)};
}

/**
 * Shuffles the deck using the given seed.
 *
 * @param seed the seed used for shuffling
 *
 * @return void
 *
 * @throws None
 */
void BalancedDice::shuffle(uint32_t seed)
{
    rollCount = 0U;
    cardsInDeck = DECK_SIZE_PAIRS;

    const uint8_t shuffleSeed = READFROM(seed, 16, 8);
    for (uint8_t i{0U}; i < 11U; i++)
    {
        deck[i].reset(shuffleSeed);
    }
}
