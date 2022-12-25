#include "Dice.h"

#include "bytes.h"
#include "random_utils.h"

#include <assert.h>

void Dice::swap(uint8_t a, uint8_t b, uint8_t size, uint8_t offset)
{
    uint8_t temp = READFROM(bits, a * size + offset, size);
    assert(temp > (uint8_t)0);
    WRITETO(bits, a * size + offset, size,
            READFROM(bits, b * size + offset, size));
    WRITETO(bits, b * size + offset, size, temp);
}

void Dice::shuffle(uint8_t seed)
{
    uint8_t diceCount = count();
    if(diceCount == 1) return;
#if 1
    bits = shuffleBits(seed, bits, diceCount, 3, DICE_PAIRS_OFFSET);
#else
    for (uint8_t i = static_cast<uint8_t>(diceCount - 1); i > 0; i -= 1)
    {
        uint8_t j = rand() % (i + 1); // TODO: Use seed
        assert(j < 8);
        swap(i, j, 3, DICE_PAIRS_OFFSET);
    }
#endif
}

uint8_t Dice::getPair(uint8_t count)
{
    return static_cast<uint8_t>(READFROM(bits, DICE_PAIRS_OFFSET + (3 * count), 3));
}

DiceResult Dice::popDice()
{
    const uint8_t c = count();
    assert(c > 0);
    set_count(c - 1);

    return DiceResult{
        static_cast<uint8_t>(diceValue()),
        getPair(c - 1)};
}

void Dice::reset()
{
    const uint8_t v = diceValue();
    bits = PAIRS_INITIAL_CONST[v - 2];
}