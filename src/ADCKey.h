#ifndef _ACROBOT_ADCKEY_H
#define _ACROBOT_ADCKEY_H

#include "Utils.h"

namespace ACRobot {

class ADCKey
{
  public:
    ADCKey(uint8_t keyPin): _keyPin(keyPin) {}
    uint8_t operator() () { return _keyValue; }
    void poll() { _keyValue = readButtons(); }

  protected:
    uint8_t _keyPin;
    uint8_t _keyValue;

    uint8_t readButtons();

  public:

  enum {
    None = 0,
    Right,
    Left,
    Up,
    Down,
    Select
  };

  // For V1.1 us this threshold
  //enum {
  //  RightIn = 50,
  //  LeftIn = 250,
  //  UpIn = 450,
  //  DownIn = 650,
  //  SelectIn = 850
  //};

  // For V1.0 comment the other threshold and use the one below:
  enum {
    RightIn = 50,
    LeftIn = 195,
    UpIn = 380,
    DownIn = 555,
    SelectIn = 790
  };
};

} // ACRobot namespace

#endif
