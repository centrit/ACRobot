#include <LiquidCrystal.h>
#include "Motor.h"
#include "ADCKey.h"

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
const uint8_t lcdData0 = 4;
const uint8_t lcdData1 = 5;
const uint8_t lcdData2 = 6;
const uint8_t lcdData3 = 7;
const uint8_t lcdAdcKey = A0;

LiquidCrystal lcd(lcdReset, lcdEnable,
                  lcdData0, lcdData1, lcdData2, lcdData3);
ADCKey key(A0);

void poll()
{
  mA.poll();
  mB.poll();
  key.poll();
}

void wait_for_start()
{
  pinMode(button, INPUT_PULLUP);
  while(getDigitalPin(button) == HIGH);
  pinMode(button, INPUT);
}

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Wait for start");
  wait_for_start();
  lcd.clear();
  lcd.print("Starting");
}

void loop()
{
  poll();
}
