#include <Arduino.h>
#include <avr/sleep.h>
#include <EEPROM.h>
#include <TinyI2CMaster.h>
#include <BalancedDice.h>

#include "eeprom_content.h"
#include "random_uint8.hpp"

#include <avr/io.h>

#ifndef cbi // Clear bit
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi // Set bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
#ifndef bit_is_set
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#endif

static bool eepromOk = false;

static uint8_t currentAddress = RNG_READINGS_ADDRESS;

// Variables for the Sleep/power down modes:
volatile boolean f_wdt = 0U;
static int wdt_counter = 0;

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect)
{
    f_wdt = 1; // set global flag
}

ISR(PCINT0_vect) {}

ISR(ADC_vect)
{
    // ADC conversion complete
}

// Unimplemented User Input Trigger
bool userInput()
{
    // Mock input when timer reaches 255 ticks. NOTE: untested.
    uint8_t currentTick = TCNT0;
    if (currentTick % 255U)
    {
        return true;
    }
    return false;
}

static uint8_t nearRandomValue = 0U;
static BalancedDice ctr{};

void setup()
{
    // https://github.com/Lorandil/ATTiny85-optimization-guide
    // Initialize ATTiny85's timer 0 to run at full cpu clock (prescaler = 1).
    // The timer will count from its starting value (which does not require to be set for this use case)
    // to 255 and overflow to 0 and continue counting until the power is cut.
    TCCR0A = 0x00U;        // normal mode
    TCCR0B = (1U << CS00); // prescaling with 1

    nearRandomValue = TCNT0;
    ctr.init(nearRandomValue);
}

static uint16_t seed = 0U;
static uint8_t n = 0U;

void loop()
{
    // Since the 'Deck of dice' is only expected to be shuffled occasionally, we can collect random seed at user input

    // If we access the timer at user input we get a pseudo random number from timer
    if (userInput())
    {
#if 0
        nearRandomValue = TCNT0;
        if (n % 2)
        {
            seed = nearRandomValue;
        }
        else
        {
            seed = seed << 8 | nearRandomValue;
        }
#else
        seed = random_uint8();
#endif

        ctr.rollDie(seed);

        n += 1U;
    }
}