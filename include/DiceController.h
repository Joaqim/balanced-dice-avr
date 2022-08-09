#include "Dice.h"
#include "DiceResult.h"

#include "dice_constants.h"

#include <stdint.h>

class DiceController
{
public:
    DiceController() : cardsInDeck{36}, bits{0b0}, rollCount{0} { shuffle(); }

    float getDiceProbability(uint8_t count);
    const inline float getTotalProbabilityWeight();

    DiceResult rollDie();

#if 1
    inline void swap(uint8_t a, uint8_t b);
    inline void shuffleDeck();
#endif

    inline void shuffle();

    Dice deck[11] = INITIAL_DECK;

    uint8_t cardsInDeck : 6; // 0..63
    uint8_t bits : 5;        // 0..31

    // 24 bytes
    FIELD(bits, rolls, 0, 3 * MAX_ROLLS_COUNT);
    uint8_t rollCount : 4; // 0..15
};
