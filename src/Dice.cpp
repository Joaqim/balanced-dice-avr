#include "Dice.h"

#include "random_utils.h"
#include "byte_utils.h"

#include <assert.h>

/**
 * Shuffles the elements of the Dice object based on the provided seed.
 *
 * @param seed the seed value used for shuffling
 *
 * @return void
 *
 * @throws None
 */
void Dice::shuffle(uint8_t seed)
{
    for (int i = pairCount - 1; i > 0; i--)
    {
        // Generate a random index in the range [0, i]
        const uint8_t j = rand_uint8_range(seed, i);

        // Swap the elements at indices i and j
        uint8_t tmp = pairs[i];
        pairs[i] = pairs[j];
        pairs[j] = tmp;
    }
}

/**
 * Retrieves the Dice pair at the specified index.
 *
 * @param count the index of the pair to retrieve
 *
 * @return the pair at the specified index
 *
 * @throws None
 */
uint8_t Dice::getPair(uint8_t count)
{
    return pairs[count];
}

/**
 * pops a dice pair from the Dice object and returns the result
 *
 * @return the result of the popped dice dice
 *
 * @throws assert error if pairCount is not greater than 0
 * @throws assert error if diceValue is not greater than 0
 */
DiceResult Dice::popDice()
{
    assert(pairCount > 0);
    assert(diceValue > 0);
    pairCount -= 1;

    return DiceResult{
        diceValue,
        pairs[pairCount]};
}
void Dice::initializePairs()
{
    pairCount = diceValue < 8U ? diceValue - 1U : 13U - diceValue;

    for (uint8_t i = 0U; i < pairCount; i += 1U)
    {
        pairs[i] = diceValue < 8U ? i + 1U : (diceValue % 7U) + i + 1;
        assert(pairs[i] > 0U);
    }
}
void Dice::reset(uint8_t shuffleSeed)
{
    initializePairs();
    shuffle(shuffleSeed);
    rollCount = 0;
}