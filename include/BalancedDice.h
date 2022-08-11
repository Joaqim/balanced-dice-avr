#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"
#include "deck_defines.h"

#include <stdint.h>

class BalancedDice
{
public:
    BalancedDice(uint16_t seed) : cardsInDeck{36}, rollCount{0} { shuffle(seed); }

    float getDiceProbability(Dice *dice);
    const inline float getTotalProbabilityWeight();

    DiceResult rollDie(uint16_t seed);

    void shuffle(uint16_t seed);

    Dice deck[11] = INITIAL_DECK;

    uint8_t cardsInDeck : 6; // 0..63

    uint8_t draws[36] = INITIAL_DRAWS;

    // 24 bytes
    uint8_t rollCount : 4; // 0..15
};
