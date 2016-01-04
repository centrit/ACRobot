#include "Motor.h"

namespace ACRobot {

void DCMotorInterface::poll(uint8_t directPin, uint8_t pwmPin)
{
  if (_power == _new_power)
    return;

  if (_new_power >= 0 && _power <= 0)
    clearDigitalPin(directPin);
  else if (_new_power < 0 && _power >= 0) {
    setDigitalPin(directPin);
    _new_power = -_new_power;
  }

  _power = _new_power;
  analogWrite(pwmPin, _power);
}

} // ACRobot namespace

