#include "DiceController.h"

#include <Arduino.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>


void setup()
{
  srand(1234);

  int counts[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  DiceController ctr{};
  for (int n{0}; n < 16; n += 1)
  {
    auto result = ctr.rollDie();
    assert(result.value > 0);
    counts[result.value - 2] += 1;
  }

  int t[12] = {};
  for (int n{0}; n < 11; n++)
  {
    const int c = counts[n];
    for (int w{0}; w < c; w += 1)
    {
      t[n] = c;
    }
  }

  assert(false);
}

void loop()
{
}