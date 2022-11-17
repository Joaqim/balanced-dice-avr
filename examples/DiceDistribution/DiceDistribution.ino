
#include <BalancedDice.h>

#include <avr/eeprom.h>

#define FRAME_DURATION 14

uint8_t lastTimeStamp, tickNum;

void setup() {
  randomSeed(analogRead(0));
}

void updateState() {

}

void draw() {

}

void loop() {
  uint8_t t, delta_t;

  t = millis();
  delta_t = t < lastTimeStamp ? t + (0xFF - lastTimeStamp) : t - lastTimeStamp;
  if (delta_t > FRAME_DURATION) {
    tickNum++;
    lastTimeStamp += FRAME_DURATION;

    updateState();
    draw();
  }
}
