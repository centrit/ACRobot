#include "Motor.h"
#include "Sonar.h"
#include "Interval.h"

using namespace ACRobot;

const uint8_t directA = 12;
const uint8_t directB = 13;
const uint8_t pwmA = 3;
const uint8_t pwmB = 11;
const uint8_t button = 2;

DCMotor mA(directA, pwmA);
DCMotor mB(directB, pwmB);

const uint8_t trigSonar = 8;
const uint8_t echoSonar = 9;

Sonar sonar(trigSonar, echoSonar);

Interval global(50);

bool poll()
{
  mA.poll();
  mB.poll();
  sonar.poll();

  return global.poll();
}

void setup()
{
  waitForStart(button);
}

void logic()
{
}

void loop()
{
  if(poll())
    logic();
}
