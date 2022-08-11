# Balanced Dice

:warning: WIP :warning:

This Library uses a deck of cards to simulate two six-sided dice being rolled.

The output tries to simulate a more fitting normal distribution of expected results even with fewer dice rolls.

Methodology involves calculating probability for multiples of same rolls in a short period and resetting and shuffling the deck every 13 draw.

Heres is the reference I followed in implementation: [Colonist.io - Designing Balanced Dice](https://blog.colonist.io/designing-balanced-dice/)

## TODO
- Consider using [std::normal_distribution](https://en.cppreference.com/w/cpp/numeric/random/normal_distribution)