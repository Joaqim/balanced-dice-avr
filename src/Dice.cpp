#include "Dice.h"

#include "bytes.h"
#include "random_utils.h"

#include <assert.h>

void Dice::swap(uint8_t a, uint8_t b, uint8_t size, uint8_t offset)
{
    uint8_t temp = READFROM(bits, a * size + offset, size);
    assert(temp > 0);
    WRITETO(bits, a * size + offset, size,
            READFROM(bits, b * size + offset, size));
    WRITETO(bits, b * size + offset, size, temp);
}

void Dice::shuffle()
{
    for (uint8_t i{count() - (uint8_t)1}; i > 0; i -= 1)
    {
        uint8_t j = rand() % (i + 1);
        assert(j < 8);
        swap(i, j, 6);
    }
}

const bool Dice::hasPair(const uint8_t i)
{
    return READFROM(bits, i + DICE_PAIRS_BITS_OFFSET, 1) > 0;
}

DiceResult Dice::popDice(const uint8_t i)
{
    assert(count() > 0);
    set_count(count() - 1);
    WRITETO(bits, i + DICE_PAIRS_BITS_OFFSET, 1, 0);
    return DiceResult{(uint8_t)READFROM(bits, i * 6, 3),
                      (uint8_t)READFROM(bits, i * 6 + 3, 3)};
}

DiceResult Dice::rollDie()
{
    uint8_t i{0};
    for (; i < 5; i += 1)
    {
        if (hasPair(i))
        {
            const uint8_t pairIndex =
                READFROM(bits, i * 3 + DICE_INDICES_OFFSET, 3);
            return popDice(pairIndex);
        }
    }
    return popDice(i);
}

const bool Dice::isEmpty()
{
    return READFROM(bits, DICE_PAIRS_COUNT_OFFSET, 6) == 0;
}

void Dice::reset()
{
    const uint8_t index = [this]()
    {
        const uint8_t v = value();
        if (v < 8)
        {
            return v - 2;
        }
        return 12 - v;
    }();
    // cout << (int)value() << ":" << (int)index << endl;
    //  WRITETO(bits, 40, 13 , (uint64_t)PAIR_COUNT_INITIAL[index]);
    bits |= ((uint64_t)PAIR_COUNT_INITIAL[index] << DICE_PAIRS_BITS_OFFSET);
    bits |= ((uint64_t)PAIR_INDICES_INITIAL << DICE_INDICES_OFFSET);
    assert(bits != 0);
}