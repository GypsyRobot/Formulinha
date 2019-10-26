#include "Arduino.h"
#include "Formulinha.h"

Servo servo;

void FormulinhaClass::init()
{
  pinMode(PIN_BUT_A, INPUT);
  pinMode(PIN_BUT_B, INPUT);

  pinMode(PIN_LINE_0, INPUT);
  pinMode(PIN_LINE_1, INPUT);
  pinMode(PIN_LINE_2, INPUT);
  pinMode(PIN_LINE_3, INPUT);
  pinMode(PIN_LINE_4, INPUT);

  pinMode(PIN_LDR, INPUT);

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_MOTOR_A1, OUTPUT);
  pinMode(PIN_MOTOR_A2, OUTPUT);
  pinMode(PIN_MOTOR_B1, OUTPUT);
  pinMode(PIN_MOTOR_B2, OUTPUT);

  pinMode(PIN_SERVO, OUTPUT);

  pinMode(PIN_ULTRASONIC_ECHO, OUTPUT);
  pinMode(PIN_ULTRASONIC_TRIGGER, OUTPUT);

  Serial.begin(115200);
  cute.init(PIN_BUZZER);
}
void FormulinhaClass::useServo()
{
  servo.attach(PIN_SERVO);
}
void FormulinhaClass::removeServo()
{
  servo.detach();
}

void FormulinhaClass::playSound(unsigned short soundIndex)
{
  cute.play(soundIndex);
}

FormulinhaClass Formulinha;
