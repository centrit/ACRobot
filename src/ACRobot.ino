#include "LCD.h"
#include "Motor.h"
#include "Interval.h"

using namespace ACRobot;

const uint8_t directA = 12;
const uint8_t directB = 13;
const uint8_t pwmA = 3;
const uint8_t pwmB = 11;
const uint8_t button = 2;

DCMotor mA(directA, pwmA);
DCMotor mB(directB, pwmB);

LCD<LCD_1602A_KEYPAD_SHIELD> lcd;

Interval global(50);

bool poll()
{
  mA.poll();
  mB.poll();
  lcd.poll();

  return global.poll();
}

void setup()
{
  lcd.print("Wait for start");
  waitForStart(button);
  lcd.clear();
  lcd.print("Starting");
}

void logic()
{
  static uint8_t cnt = 0;
  const char *str;

  switch (lcd())
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
