#ifndef _ACROBOT_MOTOR_H
#define _ACROBOT_MOTOR_H

#include "Utils.h"

namespace ACRobot {

class DCMotorInterface: public PollingInterface
{
  public:
    DCMotorInterface(): _power(0) {}
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
    DCMotor()
    {
      pinMode(directPin, OUTPUT);
      pinMode(pwmPin, OUTPUT);
    }

    void setPower(uint8_t power) { _new_power = power; poll(); };
    uint8_t operator= (uint8_t power) { _new_power = power; };

    void poll() { DCMotorInterface::poll(directPin, pwmPin); }

  private:
};

} // ACRobot namespace

#endif

