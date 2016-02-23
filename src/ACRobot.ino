#include <LiquidCrystal.h>
#include "Motor.h"
#include "ADCKey.h"
#include "Interval.h"

using namespace ACRobot;

const uint8_t directA = 12;
const uint8_t directB = 13;
const uint8_t pwmA = 3;
const uint8_t pwmB = 11;
const uint8_t button = 2;

DCMotor mA(directA, pwmA);
DCMotor mB(directB, pwmB);

const uint8_t lcdReset = 8;
const uint8_t lcdEnable = 9;
const uint8_t lcdData4 = 4;
const uint8_t lcdData5 = 5;
const uint8_t lcdData6 = 6;
const uint8_t lcdData7 = 7;
const uint8_t lcdAdcKey = A0;

LiquidCrystal lcd(lcdReset, lcdEnable,
                  lcdData4, lcdData5, lcdData6, lcdData7);
ADCKey key(A0);

Interval global(50);

bool poll()
{
  mA.poll();
  mB.poll();
  key.poll();

  return global.poll();
}

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Wait for start");
  waitForStart(button);
  lcd.clear();
  lcd.print("Starting");
}

void logic()
{
  static uint8_t cnt = 0;
  const char *str;

  switch (key())
  {
  case RightKey:
    str = "Right";
    cnt++;
    break;
  case LeftKey:
    str = "Left";
    cnt--;
    break;
  case UpKey:
    str = "Up";
    cnt += 10;
    break;
  case DownKey:
    str = "Down";
    cnt -= 10;
    break;
  case SelectKey:
    str = "Select";
    cnt = 0;
    break;
  case NoneKey:
    str = "None";
    break;
  default:
    str = "Unknown";
    break;
  }

  lcd.clear();
  lcd.print(cnt);
  lcd.setCursor(0, 1);
  lcd.print(str);
}

void loop()
{
  if(poll())
    logic();
}
