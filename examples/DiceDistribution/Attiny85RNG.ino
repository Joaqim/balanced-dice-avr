
#include <avr/io.h>

//Unimplemented User Input Trigger
bool userInput(){
    return false;
}

void setup()
{
    // https://github.com/Lorandil/ATTiny85-optimization-guide
    // Initialize ATTiny85's timer 0 to run at full cpu clock (prescaler = 1).
    // The timer will count from its starting value (which does not require to be set for this use case)
    // to 255 and overflow to 0 and continue counting until the power is cut.
    TCCR0A = 0x00;        // normal mode
    TCCR0B = (1 << CS00); // prescaling with 1
}

static uint16_t seed = 0;
static uint8_t n = 0;

void loop()
{
    // Since the 'Deck of dice' is only expected to be shuffled occasionally, we can collect random seed at user input

    // If we access the timer at user input we get a pseudo random number from timer
    if(userInput()) {
        uint8_t nearRandomValue = TCNT0;
        if(n % 2) {
            seed = nearRandomValue;
        } else {
            seed = seed << 8 | nearRandomValue;
        }

        n+= 1;
    }
}