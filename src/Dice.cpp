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

void Dice::shuffle(uint8_t seed)
{
    #if 1
    bits = shuffleBits(seed, bits, count(),  6, 1);
    #else
    assert(count() > 0);
    for (uint8_t i{count() - (uint8_t)1}; i > 0; i -= 1)
    {
        uint8_t j = rand() % (i + 1);
        assert(j < 8);
        swap(i, j, 6);
    }
    #endif
}

DiceResult Dice::popDice()
{
    const uint8_t c = count();
    assert(c > 0);
    set_count(c - 1);

    return DiceResult{
        static_cast<uint8_t>(value()),
        READFROM(bits, c * 3, 3)};
}

const bool Dice::isEmpty()
{
    return count() == 0;
}

void Dice::reset()
{
    const uint8_t v = value();
    const uint8_t count = [&v]()
    {
        if (v < 8)
        {
            return v - 2;
        }
        return 12 - v;
    }();
    set_count(count);
    set_roll_count(0);
    // cout << (int)value() << ":" << (int)index << endl;
    bits |= ((uint64_t)PAIRS_INITIAL_CONST[v - 2] << DICE_COUNT_OFFSET);
    // TODO: test alt:
    //set_pairs(PAIRS_INITIAL_CONST[v - 2]);
    assert(bits != 0);
}