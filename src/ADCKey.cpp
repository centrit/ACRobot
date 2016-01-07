#include "ADCKey.h"

namespace ACRobot {

uint8_t ADCKey::readButtons()
{
  int keyIn = analogRead(_keyPin);
  if (keyIn > 1000) return None;

  if (keyIn < RightIn) return Right;
  if (keyIn < LeftIn) return Left;
  if (keyIn < RightIn) return Up;
  if (keyIn < RightIn) return Down;
  if (keyIn < RightIn) return Select;

  return None;
}

} // ACRobot namespace

