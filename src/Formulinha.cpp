#include "Arduino.h"
#include "Formulinha.h"

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

  pinMode(PIN_ULTRASONIC_ECHO, INPUT);
  pinMode(PIN_ULTRASONIC_TRIGGER, OUTPUT);

  Serial.begin(115200);
  cute.init(PIN_BUZZER);
}
void FormulinhaClass::useServo()
{
  myServo.attach(PIN_SERVO);
}
void FormulinhaClass::removeServo()
{
  myServo.detach();
}

void FormulinhaClass::sound(unsigned short soundIndex)
{
  cute.play(soundIndex);
}

void FormulinhaClass::updateLineSensors()
{
  lineSensor[0] = analogRead(PIN_LINE_0);
  lineSensor[1] = analogRead(PIN_LINE_1);
  lineSensor[2] = analogRead(PIN_LINE_2);
  lineSensor[3] = analogRead(PIN_LINE_3);
  lineSensor[4] = analogRead(PIN_LINE_4);
}

void FormulinhaClass::forward(unsigned short leftPercentage, unsigned short rightPercentage)
{

  if (rightPercentage < 0)
    rightPercentage = 0;
  if (rightPercentage > 100)
    rightPercentage = 100;
  if (leftPercentage < 0)
    leftPercentage = 0;
  if (leftPercentage > 100)
    leftPercentage = 100;

  unsigned short rightPwm = map(rightPercentage, 0, 100, 0, 255);
  unsigned short leftPwm = map(leftPercentage, 0, 100, 0, 255);

  analogWrite(PIN_MOTOR_A1, 0);
  analogWrite(PIN_MOTOR_A2, rightPwm);
  analogWrite(PIN_MOTOR_B1, 0);
  analogWrite(PIN_MOTOR_B2, leftPwm);
}

void FormulinhaClass::backward(unsigned short leftPercentage, unsigned short rightPercentage)
{

  if (rightPercentage < 0)
    rightPercentage = 0;
  if (rightPercentage > 100)
    rightPercentage = 100;
  if (leftPercentage < 0)
    leftPercentage = 0;
  if (leftPercentage > 100)
    leftPercentage = 100;

  unsigned short rightPwm = map(rightPercentage, 0, 100, 0, 255);
  unsigned short leftPwm = map(leftPercentage, 0, 100, 0, 255);

  analogWrite(PIN_MOTOR_A1, rightPwm);
  analogWrite(PIN_MOTOR_A2, 0);
  analogWrite(PIN_MOTOR_B1, leftPwm);
  analogWrite(PIN_MOTOR_B2, 0);
}

void FormulinhaClass::left(unsigned short leftPercentage, unsigned short rightPercentage)
{

  if (rightPercentage < 0)
    rightPercentage = 0;
  if (rightPercentage > 100)
    rightPercentage = 100;
  if (leftPercentage < 0)
    leftPercentage = 0;
  if (leftPercentage > 100)
    leftPercentage = 100;

  unsigned short rightPwm = map(rightPercentage, 0, 100, 0, 255);
  unsigned short leftPwm = map(leftPercentage, 0, 100, 0, 255);

  analogWrite(PIN_MOTOR_A1, 0);
  analogWrite(PIN_MOTOR_A2, rightPwm);
  analogWrite(PIN_MOTOR_B1, leftPwm);
  analogWrite(PIN_MOTOR_B2, 0);
}

void FormulinhaClass::right(unsigned short leftPercentage, unsigned short rightPercentage)
{

  if (rightPercentage < 0)
    rightPercentage = 0;
  if (rightPercentage > 100)
    rightPercentage = 100;
  if (leftPercentage < 0)
    leftPercentage = 0;
  if (leftPercentage > 100)
    leftPercentage = 100;

  unsigned short rightPwm = map(rightPercentage, 0, 100, 0, 255);
  unsigned short leftPwm = map(leftPercentage, 0, 100, 0, 255);

  analogWrite(PIN_MOTOR_A1, rightPwm);
  analogWrite(PIN_MOTOR_A2, 0);
  analogWrite(PIN_MOTOR_B1, 0);
  analogWrite(PIN_MOTOR_B2, leftPwm);
}

unsigned int FormulinhaClass::light()
{
  unsigned int currentLight = analogRead(PIN_LDR);
  return currentLight;
}

float FormulinhaClass::distance()
{
  digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_ULTRASONIC_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);

  unsigned long durationMicroSeconds = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);
  float distanceCm = durationMicroSeconds / 2.0 * 0.0343;
  if (distanceCm > 400 || distanceCm <= 0)
  {
    return -1.0;
  }
  else
  {
    return distanceCm;
  }
}

void FormulinhaClass::led(unsigned short redPercentage, unsigned short greenPercentage, unsigned short bluePercentage)
{
  if (redPercentage < 0)
    redPercentage = 0;
  if (redPercentage > 100)
    redPercentage = 100;
  if (greenPercentage < 0)
    greenPercentage = 0;
  if (greenPercentage > 100)
    greenPercentage = 100;
  if (bluePercentage < 0)
    bluePercentage = 0;
  if (bluePercentage > 100)
    bluePercentage = 100;

  unsigned short redPwm = map(redPercentage, 0, 100, 0, 255);
  unsigned short greenPwm = map(greenPercentage, 0, 100, 0, 255);
  unsigned short bluePwm = map(bluePercentage, 0, 100, 0, 255);

  analogWrite(PIN_RED, redPwm);
  analogWrite(PIN_GREEN, greenPwm);
  analogWrite(PIN_BLUE, bluePwm);
}

bool FormulinhaClass::buttonA()
{
  bool buttonAStatus = digitalRead(PIN_BUT_A);
  if (buttonAStatus == 0)
  {
    delay(30); //30ms pra garantir um debounce
    return true;
  }
  else
  {
    return false;
  }
}
bool FormulinhaClass::buttonB()
{
  bool buttonBStatus = digitalRead(PIN_BUT_B);
  if (buttonBStatus == 0)
  {
    delay(30); //30ms pra garantir um debounce
    return true;
  }
  else
  {
    return false;
  }
}

void FormulinhaClass::servo(unsigned short angle)
{
  if (angle > 180)
    angle = 180;
  if (angle < 0)
    angle = 0;
  myServo.write(angle);
  delay(30); //30ms pra garantir que não estrague o servo por excesso de movimentos
}

FormulinhaClass Formulinha;
