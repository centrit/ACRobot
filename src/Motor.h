#ifndef _ACROBOT_MOTOR_H
#define _ACROBOT_MOTOR_H

#include "Utils.h"

namespace ACRobot {

class DCMotorInterface: public PollingInterface
{
  public:
    DCMotorInterface(uint8_t directPin, uint8_t pwmPin): _power(0)
    {
      pinMode(directPin, OUTPUT);
      pinMode(pwmPin, OUTPUT);
    }
    uint8_t operator= (uint8_t power) { _new_power = power; };
    void setPower(uint8_t power) { _power = power; }

  protected:
    void poll(uint8_t directPin, uint8_t pwmPin);

    uint8_t _new_power;
    uint8_t _power;
};

template < uint8_t directPin, uint8_t pwmPin >
class DCMotor: public DCMotorInterface
{
  public:
    DCMotor(): DCMotorInterface(directPin, pwmPin) {}
    void poll() { DCMotorInterface::poll(directPin, pwmPin); }

  private:
};

} // ACRobot namespace

#endif

