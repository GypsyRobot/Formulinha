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

  delay(1000); //espera um segundo quando inicia tudo para estabilizar
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

void FormulinhaClass::averageLineSensors()
{

  for (unsigned short i = 0; i < SAMPLES_PER_AVERAGE; i++)
  {
    lineSensorMovingAverageSamples[0][i] = 500; //reseta as médias
    lineSensorMovingAverageSamples[1][i] = 500;
    lineSensorMovingAverageSamples[2][i] = 500;
    lineSensorMovingAverageSamples[3][i] = 500;
    lineSensorMovingAverageSamples[4][i] = 500;

    lineSensorMovingAverage[0] = 0;
    lineSensorMovingAverage[1] = 0;
    lineSensorMovingAverage[2] = 0;
    lineSensorMovingAverage[3] = 0;
    lineSensorMovingAverage[4] = 0;
  }

  for (unsigned short i = 0; i < SAMPLES_PER_AVERAGE; i++)
  {
    lineSensorMovingAverageSamples[0][i] = analogRead(PIN_LINE_0);
    lineSensorMovingAverageSamples[1][i] = analogRead(PIN_LINE_1);
    lineSensorMovingAverageSamples[2][i] = analogRead(PIN_LINE_2);
    lineSensorMovingAverageSamples[3][i] = analogRead(PIN_LINE_3);
    lineSensorMovingAverageSamples[4][i] = analogRead(PIN_LINE_4);

    lineSensorMovingAverage[0] += lineSensorMovingAverageSamples[0][i];
    lineSensorMovingAverage[1] += lineSensorMovingAverageSamples[1][i];
    lineSensorMovingAverage[2] += lineSensorMovingAverageSamples[2][i];
    lineSensorMovingAverage[3] += lineSensorMovingAverageSamples[3][i];
    lineSensorMovingAverage[4] += lineSensorMovingAverageSamples[4][i];
  }
  lineSensorMovingAverage[0] = lineSensorMovingAverage[0] / SAMPLES_PER_AVERAGE;
  lineSensorMovingAverage[1] = lineSensorMovingAverage[1] / SAMPLES_PER_AVERAGE;
  lineSensorMovingAverage[2] = lineSensorMovingAverage[2] / SAMPLES_PER_AVERAGE;
  lineSensorMovingAverage[3] = lineSensorMovingAverage[3] / SAMPLES_PER_AVERAGE;
  lineSensorMovingAverage[4] = lineSensorMovingAverage[4] / SAMPLES_PER_AVERAGE;
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

void FormulinhaClass::calibrateLineSensors(bool automatic)
{
  bool sideTurning = 0;
  unsigned short sideTurningCounter = 0;

  sound(S_CONNECTION);
  led(100, 0, 100);

  if (automatic == true)
  {

    left(100, 100);
    delay(CALIBRATE_READING_DELAY);
  }

  for (int i = 0; i < SAMPLES_PER_SENSOR; i++)
  {
    if (automatic == true)
    {
      sideTurningCounter++;
      if (sideTurningCounter >= 5)
      {
        sideTurningCounter = 0;
        if (sideTurning == 0)
          sideTurning = 1;
        else
          sideTurning = 0;
      }

      if (sideTurning == 0)
      {
        right(100, 100);
      }
      else
      {
        left(100, 100);
      }
    }

    updateLineSensors();
    if (lineSensor[0] < lineSensorMin[0])
      lineSensorMin[0] = lineSensor[0];
    if (lineSensor[0] > lineSensorMax[0])
      lineSensorMax[0] = lineSensor[0];
    if (lineSensor[1] < lineSensorMin[1])
      lineSensorMin[1] = lineSensor[1];
    if (lineSensor[1] > lineSensorMax[1])
      lineSensorMax[1] = lineSensor[1];
    if (lineSensor[2] < lineSensorMin[2])
      lineSensorMin[2] = lineSensor[2];
    if (lineSensor[2] > lineSensorMax[2])
      lineSensorMax[2] = lineSensor[2];
    if (lineSensor[3] < lineSensorMin[3])
      lineSensorMin[3] = lineSensor[3];
    if (lineSensor[3] > lineSensorMax[3])
      lineSensorMax[3] = lineSensor[3];
    if (lineSensor[4] < lineSensorMin[4])
      lineSensorMin[4] = lineSensor[4];
    if (lineSensor[4] > lineSensorMax[4])
      lineSensorMax[4] = lineSensor[4];

    lineSensorMed[0] = lineSensorMin[0] + ((lineSensorMax[0] - lineSensorMin[0]) / 2);
    lineSensorMed[1] = lineSensorMin[1] + ((lineSensorMax[1] - lineSensorMin[1]) / 2);
    lineSensorMed[2] = lineSensorMin[2] + ((lineSensorMax[2] - lineSensorMin[2]) / 2);
    lineSensorMed[3] = lineSensorMin[3] + ((lineSensorMax[3] - lineSensorMin[3]) / 2);
    lineSensorMed[4] = lineSensorMin[4] + ((lineSensorMax[4] - lineSensorMin[4]) / 2);

    lineSensorSamples[0][i] = lineSensorMed[0];
    lineSensorSamples[1][i] = lineSensorMed[1];
    lineSensorSamples[2][i] = lineSensorMed[2];
    lineSensorSamples[3][i] = lineSensorMed[3];
    lineSensorSamples[4][i] = lineSensorMed[4];

    Serial.print(lineSensorSamples[0][i]);
    Serial.print("\t");
    Serial.print(lineSensorSamples[1][i]);
    Serial.print("\t");
    Serial.print(lineSensorSamples[2][i]);
    Serial.print("\t");
    Serial.print(lineSensorSamples[3][i]);
    Serial.print("\t");
    Serial.print(lineSensorSamples[4][i]);
    Serial.print("\n");

    delay(CALIBRATE_READING_DELAY);
  }

  forward(0, 0);

  sound(S_HAPPY);
  led(0, 0, 0);
}

void FormulinhaClass::followLine(unsigned short weightA, unsigned short weightB)
{
  updateLineSensors();

  if (lineSensor[2] > lineSensorMed[2])
  {
    forward(100, 100);
  }
  else
  {
    speedRight = (lineSensor[0] * weightB + lineSensor[1] * weightA) / (weightA + weightB);
    speedLeft = (lineSensor[4] * weightB + lineSensor[3] * weightA) / (weightA + weightB);

    unsigned short leftPercentage = map(speedLeft * 3 / 2, lineSensorMin[0], lineSensorMax[0], 0, 100);
    unsigned short rightPercentage = map(speedRight * 3 / 2, lineSensorMin[4], lineSensorMax[4], 0, 100);

    // Serial.print(Formulinha.lineSensor[0]);
    // Serial.print("\t");
    // Serial.print(Formulinha.lineSensor[1]);
    // Serial.print("\t");
    // Serial.print(Formulinha.lineSensor[2]);
    // Serial.print("\t");
    // Serial.print(Formulinha.lineSensor[3]);
    // Serial.print("\t");
    // Serial.print(Formulinha.lineSensor[4]);
    // Serial.print("\t");

    // Serial.print(leftPercentage);
    // Serial.print(" Speed Left\t");
    // Serial.print(rightPercentage);
    // Serial.print(" Speed Right\n");

    if (leftPercentage < 20 && rightPercentage < 20)
    {

      if (leftPercentage > rightPercentage)
      {
        forward(leftPercentage * 10, rightPercentage);
      }
      else if (leftPercentage < rightPercentage)
      {
        forward(leftPercentage, rightPercentage * 10);
      }
      else
      {
        forward(leftPercentage * 15, rightPercentage * 5);
      }

      //forward(0, 0); //se só encontrar branco ele para
      if (lineLost == false)
      {
        sound(S_DISCONNECTION);
        led(255, 0, 0);
        lineLost = true;
      }
    }
    else
    {
      forward(leftPercentage, rightPercentage);
      led(0, 0, 255);
      lineLost = false;
    }
  }
}

void FormulinhaClass::avoidLine()
{
  averageLineSensors();
  if (lineSensorMovingAverage[0] > lineSensorMed[0] || lineSensorMovingAverage[1] > lineSensorMed[1] || lineSensorMovingAverage[2] > lineSensorMed[2] || lineSensorMovingAverage[3] > lineSensorMed[3] || lineSensorMovingAverage[4] > lineSensorMed[4])
  {
    if (avoidSide == false)
    {
      led(100, 0, 0);
      backward(100, 100);
      sound(S_HAPPY);
      delay(300);
      right(100, 100);
      delay(400);
      avoidSide = true;
    }
    else
    {
      led(100, 0, 0);
      backward(100, 100);
      sound(S_CONFUSED);
      delay(200);
      left(100, 100);
      delay(800);
      avoidSide = false;
    }
  }
  else
  {
    led(0, 0, 100);
    forward(100, 100);
  }
}

void FormulinhaClass::partyMode()
{

  if (light() < 400)
  {

    genericFlag = false;

    right(100, 100);

    led(255, 0, 0);
    delay(30);
    led(255, 255, 0);
    delay(30);
    led(255, 255, 255);
    delay(30);
    led(0, 255, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    led(0, 0, 0);
    delay(30);
    led(0, 255, 0);
    delay(30);
    led(255, 0, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    sound(S_HAPPY);

    left(100, 100);

    led(255, 0, 0);
    delay(30);
    led(255, 255, 0);
    delay(30);
    led(255, 255, 255);
    delay(30);
    led(0, 255, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    led(0, 0, 0);
    delay(30);
    led(0, 255, 0);
    delay(30);
    led(255, 0, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    sound(S_SURPRISE);

    forward(100, 100);

    led(255, 0, 0);
    delay(30);
    led(255, 255, 0);
    delay(30);
    led(255, 255, 255);
    delay(30);
    led(0, 255, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    led(0, 0, 0);
    delay(30);
    led(0, 255, 0);
    delay(30);
    led(255, 0, 255);
    delay(30);

    sound(S_HAPPY_SHORT);

    backward(100, 100);

    led(255, 0, 0);
    delay(30);
    led(255, 255, 0);
    delay(30);
    led(255, 255, 255);
    delay(30);
    led(0, 255, 255);
    delay(30);
    led(0, 0, 255);
    delay(30);
    led(0, 0, 0);
    delay(30);
    led(0, 255, 0);
    delay(30);
    led(255, 0, 255);
    delay(30);

    sound(S_MODE2);
  }
  else
  {
    forward(0, 0);
    led(0, 0, 0);
    if (genericFlag == false)
    {
      delay(500);
      sound(S_SAD);
      genericFlag = true;
    }
  }
}

FormulinhaClass Formulinha;
