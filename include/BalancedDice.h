#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"
#include "deck_defines.h"

#include <stdint.h>

class BalancedDice
{
public:
    BalancedDice(uint16_t seed) {
        shuffle(seed);
    }

    float getDiceProbability(Dice *dice);
    const inline float getTotalProbabilityWeight();

    DiceResult rollDie(uint16_t seed);

    void shuffleDraws();
    void shuffle(uint16_t seed);

    Dice deck[DECK_SIZE];

    uint8_t cardsInDeck : 6; // 0..63

    uint8_t draws[DECK_SIZE_PAIRS] = INITIAL_DRAWS;

    uint8_t rollCount : 4; // 0..15
};
