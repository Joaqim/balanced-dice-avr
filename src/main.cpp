#include "../include/BalancedDice.h"

#include <Arduino.h>
#include <stdint.h>
#include <assert.h>


void setup()
{
  const uint16_t seed = 54321;
  int counts[11] = {0};
  BalancedDice ctr{seed};
  for (int n{0}; n < 16; n += 1)
  {
    const uint16_t newSeed = static_cast<uint16_t>(1974 * n);
    auto result = ctr.rollDie(newSeed);
    assert(result.value > 0);
    counts[result.value - 2] += 1;
  }

  #if 0
  int t[12] = {};
  for (int n{0}; n < 11; n++)
  {
    const int c = counts[n];
    for (int w{0}; w < c; w += 1)
    {
      t[n] = c;
    }
  }

  #endif
}

void loop()
{
}