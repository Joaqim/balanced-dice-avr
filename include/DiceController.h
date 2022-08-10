#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"
#include "deck_defines.h"

#include <stdint.h>

class DiceController
{
public:
    DiceController() : cardsInDeck{36}, rollCount{0} { shuffle(); }

    float getDiceProbability(Dice *dice);
    const inline float getTotalProbabilityWeight();

    DiceResult rollDie();

#if 1
    inline void swap(uint8_t a, uint8_t b);
    inline void shuffleDeck();
#endif

    inline void shuffle();

    Dice deck[11] = INITIAL_DECK;

    uint8_t cardsInDeck : 6; // 0..63

    uint8_t draws[36] = INITIAL_DRAWS;

    // 24 bytes
    uint8_t rollCount : 4; // 0..15
};
