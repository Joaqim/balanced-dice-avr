#include "DiceController.h"

#include "dice_tables.h"
#include "shuffle_macro.h"

#include <assert.h>

decl_shuffle(Dice);

float DiceController::getDiceProbability(uint8_t count)
{
    assert(count > 0);
    return dice_probability_lookup_table[rollCount][count - 1];
}

const float DiceController::getTotalProbabilityWeight()
{
    float result{0};
    for (int i{0}; i < 11; i += 1)
    {
        const uint8_t count = deck[i].count();
        if (count > 0)
        {
            result += getDiceProbability(count);
        }
    }
    return result;
}

DiceResult DiceController::rollDie()
{
    if (rollCount > MIN_CARDS_BEFORE_SHUFFLE)
    {
        shuffle();
    }

    const float totalProbability = getTotalProbabilityWeight();

    float targetRandomNumber = randfloat() * totalProbability;

    Dice *dice;
    for (uint8_t i{0}; i < 11; i += 1)
    {
        dice = &deck[i];
        const uint8_t count = dice->count();
        if (count > 0)
        {
            const float probability = getDiceProbability(count);
            if (targetRandomNumber <= probability)
            {
                cardsInDeck -= 1;
                rollCount += 1;
                WRITETO(bits, i, 1, 1);
                return dice->rollDie();
            }
            targetRandomNumber -= probability;
        }
    }
    return DiceResult{0, 0};
    assert(false);
}

#if 1
void DiceController::swap(uint8_t a, uint8_t b)
{
    Dice temp = deck[a];
    deck[a] = deck[b];
    deck[b] = temp;
}

void DiceController::shuffleDeck() { shuffle_Dice(deck, 12); }
#endif

void DiceController::shuffle()
{
    rollCount = 0;
    cardsInDeck = 36;
    bits = 0b0;
    // shuffleDeck();
    for (uint8_t i{0}; i < 11; i++)
    {
        deck[i].reset();
        deck[i].shuffle();
    }
}
