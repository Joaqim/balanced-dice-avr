#pragma once
#include "DiceController.h"
#include "DiceResult.h"

class BalancedDice {
    DiceResult throwDice() {
        return ctr.rollDie();
    }

    void shuffle() {
        ctr.shuffle();
    };

    DiceController ctr{};
};
