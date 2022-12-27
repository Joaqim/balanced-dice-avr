#include "Dice.h"

#include "random_utils.h"
#include "byte_utils.h"

#include <assert.h>

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

uint8_t Dice::getPair(uint8_t count)
{
    return pairs[count];
}

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