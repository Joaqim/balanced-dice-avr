#pragma once
#include "common.h"


struct DiceResult
{
    DiceResult(const uint8_t value_, const uint8_t dice1_)
        : value{value_},
          dice1{dice1_},
          dice2{static_cast<uint8_t>(value_ - dice1_)} {}

    uint8_t value : 4;
    uint8_t dice1 : 3;
    uint8_t dice2 : 3;
};
