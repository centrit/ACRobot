#include "LCD.h"
#include "Motor.h"
#include "Interval.h"

using namespace ACRobot;

uint8_t power = 75;

const uint8_t directA = 12;
const uint8_t directB = 13;
const uint8_t pwmA = 3;
const uint8_t pwmB = 11;
const uint8_t button = 2;

DCMotor mA(directA, pwmA);
DCMotor mB(directB, pwmB);

LCD<LCD_1602A_KEYPAD_SHIELD> lcd;

enum State {
    GLOBAL = 0,
    SCREEN = 1,
    BLINK  = 2
};

const unsigned long GLOBAL_INTERVAL = 50;
const unsigned long SCREEN_INTERVAL = 100;
const unsigned long BLINK_INTERVAL  = 1000;

const uint8_t NUMBER_OF_INTERVALS = 3;
Intervals<NUMBER_OF_INTERVALS> intervals;

int poll()
{
  mA.poll();
  mB.poll();
  lcd.poll();

  return intervals.poll();
}

void setup()
{
  lcd.print("Wait for start");

  intervals[GLOBAL] = GLOBAL_INTERVAL;
  intervals[SCREEN] = SCREEN_INTERVAL;
  intervals[BLINK]  = BLINK_INTERVAL;

  waitForStart(button);

  lcd.clear();
  lcd.print("Starting");
}


static uint8_t cnt = 0;
static const char *str = "Init";

void logic()
{
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
}

void screen()
{
  lcd.clear();
  lcd.print(cnt);
  lcd.setCursor(0, 1);
  lcd.print(str);
}

void blink()
{
    power = -power;
}

void loop()
{
  switch (poll())
  {
    case GLOBAL:
      logic();
      break;
    case SCREEN:
      screen();
      break;
    case BLINK:
      blink();
      break;
  }
}
