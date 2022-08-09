#pragma once
#include <stdint.h>

struct DiceResult
{
    DiceResult(uint8_t dice1_, uint8_t dice2_)
        : dice1{dice1_},
          dice2{dice2_},
          value{dice1_ + dice2_} {}
    const uint8_t dice1 : 3;
    const uint8_t dice2 : 3;
    const uint8_t value : 4;
};

