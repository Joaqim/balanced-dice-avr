#include "DiceController.h"

#include "dice_tables.h"
#include "shuffle_macro.h"

#include <assert.h>

decl_shuffle(Dice);
decl_shuffle(uint8_t);

float DiceController::getDiceProbability(Dice *dice)
{
    assert(dice->count() > 0);
    const float probabilityModifier = 1 - (dice->roll_count() * PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED);
    const float probability = dice_probability_lookup_table[rollCount][dice->count() - 1] * probabilityModifier;
    if (probability < 1)
        return 0;
    return probability;
}

const float DiceController::getTotalProbabilityWeight()
{
    float result{0};
    for (int i{0}; i < DECK_SIZE; i += 1)
    {
        Dice *dice = &deck[i];
        if (dice->count() > 0)
        {
            result += getDiceProbability(dice);
        }
    }
    return result;
}

DiceResult DiceController::rollDie()
{
    if (rollCount > MIN_ROLLS_BEFORE_RESHUFFLING)
    {
        shuffle();
    }

    const float totalProbability = getTotalProbabilityWeight();

    float targetRandomNumber = randfloat() * totalProbability;

    Dice *dice;
    for (uint8_t i{rollCount}; i < DECK_SIZE_PAIRS; i += 1)
    {
        assert(i < 15);
        dice = &deck[draws[i]];
        if (dice->count() > 0)
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
    return DiceResult{0, 0};
}

#if 1
void DiceController::swap(uint8_t a, uint8_t b)
{
    Dice temp = deck[a];
    deck[a] = deck[b];
    deck[b] = temp;
}

void DiceController::shuffleDeck()
{
    // shuffle_Dice(deck, 12);
    shuffle_uint8_t(draws, DECK_SIZE_PAIRS);
}
#endif

void DiceController::shuffle()
{
    rollCount = 0;
    cardsInDeck = DECK_SIZE_PAIRS;
    shuffleDeck();
    for (uint8_t i{0}; i < 11; i++)
    {
        deck[i].reset();
        deck[i].shuffle();
    }
}
