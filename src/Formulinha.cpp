#include "Formulinha.h"

void FormulinhaClass::Start()
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

void FormulinhaClass::WhiteLine()
{
  whiteLine = true;
}

void FormulinhaClass::BlackLine()
{
  whiteLine = false;
}
void FormulinhaClass::UseServo()
{
  myServo.attach(PIN_SERVO);
}
void FormulinhaClass::RemoveServo()
{
  myServo.detach();
}

void FormulinhaClass::Sound(unsigned short soundIndex)
{
  cute.play(soundIndex);
}

void FormulinhaClass::UpdateLineSensors()
{
  if (whiteLine == false)
  {
    lineSensor[0] = analogRead(PIN_LINE_0);
    lineSensor[1] = analogRead(PIN_LINE_1);
    lineSensor[2] = analogRead(PIN_LINE_2);
    lineSensor[3] = analogRead(PIN_LINE_3);
    lineSensor[4] = analogRead(PIN_LINE_4);
  }
  else
  {
    lineSensor[0] = 1023 - analogRead(PIN_LINE_0);
    lineSensor[1] = 1023 - analogRead(PIN_LINE_1);
    lineSensor[2] = 1023 - analogRead(PIN_LINE_2);
    lineSensor[3] = 1023 - analogRead(PIN_LINE_3);
    lineSensor[4] = 1023 - analogRead(PIN_LINE_4);
  }
}

void FormulinhaClass::AverageLineSensors()
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
    if (whiteLine == false)
    {
      lineSensorMovingAverageSamples[0][i] = analogRead(PIN_LINE_0);
      lineSensorMovingAverageSamples[1][i] = analogRead(PIN_LINE_1);
      lineSensorMovingAverageSamples[2][i] = analogRead(PIN_LINE_2);
      lineSensorMovingAverageSamples[3][i] = analogRead(PIN_LINE_3);
      lineSensorMovingAverageSamples[4][i] = analogRead(PIN_LINE_4);
    }
    else
    {
      lineSensorMovingAverageSamples[0][i] = 1023 - analogRead(PIN_LINE_0);
      lineSensorMovingAverageSamples[1][i] = 1023 - analogRead(PIN_LINE_1);
      lineSensorMovingAverageSamples[2][i] = 1023 - analogRead(PIN_LINE_2);
      lineSensorMovingAverageSamples[3][i] = 1023 - analogRead(PIN_LINE_3);
      lineSensorMovingAverageSamples[4][i] = 1023 - analogRead(PIN_LINE_4);
    }
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

void FormulinhaClass::Forward(unsigned short leftPercentage, unsigned short rightPercentage)
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

void FormulinhaClass::Backward(unsigned short leftPercentage, unsigned short rightPercentage)
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

void FormulinhaClass::Left(unsigned short leftPercentage, unsigned short rightPercentage)
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

void FormulinhaClass::Right(unsigned short leftPercentage, unsigned short rightPercentage)
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

unsigned int FormulinhaClass::Light()
{
  unsigned int currentLight = analogRead(PIN_LDR);
  return currentLight;
}

float FormulinhaClass::Distance()
{
  unsigned short numberOfSamples = 10;
  float distanceSamples[numberOfSamples];
  float averageDistance = 0;

  for (unsigned short i = 0; i < numberOfSamples; i++)
  {
    digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_ULTRASONIC_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);

    unsigned long durationMicroSeconds = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);
    float distanceCm = durationMicroSeconds / 2.0 * 0.0343;
    distanceSamples[i] = distanceCm;
    averageDistance += distanceSamples[i];
  }
  averageDistance = averageDistance / numberOfSamples;

  if (averageDistance <= 1)
  {
    return -1;
  }
  else if (averageDistance > 400)
  {
    return 999;
  }
  else
  {
    return averageDistance;
  }
}

void FormulinhaClass::Led(unsigned short redPercentage, unsigned short greenPercentage, unsigned short bluePercentage)
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

bool FormulinhaClass::ButtonA()
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
bool FormulinhaClass::ButtonB()
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

void FormulinhaClass::Servo(unsigned short angle)
{
  if (angle > 180)
    angle = 180;
  if (angle < 0)
    angle = 0;
  myServo.write(angle);
  delay(30); //30ms pra garantir que não estrague o servo por excesso de movimentos
}

void FormulinhaClass::CalibrateLineSensors()
{
  bool automatic = false;

  bool sideTurning = 0;
  unsigned short sideTurningCounter = 0;

  Sound(S_CONNECTION);
  Sound(S_CONNECTION);
  Sound(S_CONNECTION);
  Sound(S_CONNECTION);
  Sound(S_CONNECTION);

  Led(100, 0, 100);
  delay(2000);
  genericFlag = true;

  if (automatic == true)
  {

    Left(100, 100);
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
        Right(100, 100);
      }
      else
      {
        Left(100, 100);
      }
    }

    UpdateLineSensors();
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

  Forward(0, 0);

  Sound(S_HAPPY);
  Led(0, 0, 0);
}

void FormulinhaClass::FollowLine()
{
  unsigned short weightA = 1;
  unsigned short weightB = 2;
  UpdateLineSensors();

  if (lineSensor[2] > lineSensorMed[2])
  {
    Forward(100, 100);
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
        Forward(leftPercentage * 10, rightPercentage);
      }
      else if (leftPercentage < rightPercentage)
      {
        Forward(leftPercentage, rightPercentage * 10);
      }
      else
      {
        Forward(leftPercentage * 15, rightPercentage * 5);
      }

      //forward(0, 0); //se só encontrar branco ele para
      if (lineLost == false)
      {
        Sound(S_DISCONNECTION);
        Led(255, 0, 0);
        lineLost = true;
      }
    }
    else
    {
      Forward(leftPercentage, rightPercentage);
      Led(0, 0, 255);
      lineLost = false;
    }
  }
}

void FormulinhaClass::AvoidMovement(bool activate)
{
  if (activate == true)
  {
    if (avoidSide == false)
    {
      Led(100, 0, 0);
      Backward(100, 100);
      Sound(S_HAPPY);
      delay(300);
      Right(100, 100);
      delay(400);
      avoidSide = true;
    }
    else
    {
      Led(100, 0, 0);
      Backward(100, 100);
      Sound(S_CONFUSED);
      delay(200);
      Left(100, 100);
      delay(800);
      avoidSide = false;
    }
  }
  else
  {
    //Led(0, 0, 100);
    //Forward(100, 100);
  }
}

void FormulinhaClass::AvoidLine()
{
  AverageLineSensors();
  if (lineSensorMovingAverage[0] > lineSensorMed[0] || lineSensorMovingAverage[1] > lineSensorMed[1] || lineSensorMovingAverage[2] > lineSensorMed[2] || lineSensorMovingAverage[3] > lineSensorMed[3] || lineSensorMovingAverage[4] > lineSensorMed[4])
  {
    AvoidMovement(true);
  }
  else
  {
    AvoidMovement(false);
  }
}

void FormulinhaClass::PartyMode()
{

  if (Light() < 250)
  {

    genericFlag = false;

    Right(100, 100);
    Sound(S_HAPPY);

    Led(255, 0, 0);
    delay(30);
    Led(255, 255, 0);
    delay(30);
    Led(255, 255, 255);
    delay(30);
    Led(0, 255, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(0, 0, 0);
    delay(30);
    Led(0, 255, 0);
    delay(30);
    Led(255, 0, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(255, 0, 0);
    delay(30);
    Led(255, 255, 0);
    delay(30);
    Led(255, 255, 255);
    delay(30);
    Led(0, 255, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(0, 0, 0);
    delay(30);
    Led(0, 255, 0);
    delay(30);
    Led(255, 0, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(255, 0, 0);
    delay(30);
    Led(255, 255, 0);
    delay(30);
    Led(255, 255, 255);
    delay(30);
    Led(0, 255, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(0, 0, 0);
    delay(30);
    Led(0, 255, 0);
    delay(30);
    Led(255, 0, 255);
    delay(30);
    Led(255, 0, 0);
    delay(30);
    Led(255, 255, 0);
    delay(30);
    Led(255, 255, 255);
    delay(30);
    Led(0, 255, 255);
    delay(30);
    Led(0, 0, 255);
    delay(30);
    Led(0, 0, 0);
    delay(30);
    Led(0, 255, 0);
    delay(30);
    Led(255, 0, 255);
    delay(30);
  }
  else
  {
    Forward(0, 0);
    Led(0, 0, 0);
    if (genericFlag == false)
    {
      delay(500);
      Sound(S_SAD);
      genericFlag = true;
    }
  }
}

void FormulinhaClass::ScrollModes()
{

  if (ButtonA() == true)
  {
    Forward(0, 0); //para o robô quando troca de modo
    Sound(S_HAPPY_SHORT);
    delay(500); /*  */
    currentMode++;
    if (currentMode > 3)
    {
      currentMode = 0;
    }
  }

  switch (currentMode)
  {
  case 0:
    Led(255, 0, 255);
    delay(500);
    if (genericFlag == false)
    {
      CalibrateLineSensors();
    }
    break;
  case 1:
    Led(255, 0, 0);
    PartyMode();
    break;
  case 2:
    Led(0, 255, 0);
    AvoidLine();
    genericFlag = false;
    break;
  case 3:
    Led(0, 0, 255);
    FollowLine();
    genericFlag = false;
    break;
  }
}

void FormulinhaClass::AvoidObject()
{
  if (Distance() < 10) //if there is an object closer than 10 cm
  {
    AvoidMovement(true);
  }
  else
  {
    AvoidMovement(false);
  }
}

bool FormulinhaClass::AttackObject(unsigned int distance)
{
  float currentDistance = Distance();
  // Serial.println(currentDistance);

  if (currentDistance < distance && currentDistance != -1)
  {
    Forward(100, 100);
    //Sound(S_OHOOH);
    //delay(200);
    return true;
  }
  else
  {
    return false;
  }
}

void FormulinhaClass::Sumo()
{
  if (AttackObject(70) == true)
  {
    Led(100, 100, 100);
  }
  else
  {
    Forward(100, 100);
    Right(100, 100);
    Led(100, 0, 100);
  }
  AvoidLine();
}

void FormulinhaClass::Iniciar() { Start(); }
void FormulinhaClass::LinhaBranca() { WhiteLine(); }
void FormulinhaClass::LinhaPreta() { BlackLine(); }
void FormulinhaClass::UsarServo() { UseServo(); }
void FormulinhaClass::RemoverServo() { RemoveServo(); }
void FormulinhaClass::Som(unsigned short arg) { Sound(arg); }
void FormulinhaClass::AtualizarSensorDeLinha() { UpdateLineSensors(); }
void FormulinhaClass::MediaSensorDeLinha() { AverageLineSensors(); }
void FormulinhaClass::Frente(unsigned short argA, unsigned short argB) { Forward(argA, argB); }
void FormulinhaClass::Tras(unsigned short argA, unsigned short argB) { Backward(argA, argB); }
void FormulinhaClass::Esquerda(unsigned short argA, unsigned short argB) { Left(argA, argB); }
void FormulinhaClass::Direita(unsigned short argA, unsigned short argB) { Right(argA, argB); }
unsigned int FormulinhaClass::Luz() { Light(); }
float FormulinhaClass::Distancia() { Distance(); }
bool FormulinhaClass::BotaoA() { ButtonA(); }
bool FormulinhaClass::BotaoB() { ButtonB(); }
void FormulinhaClass::CalibrarSensorDeLinha() { CalibrateLineSensors(); }
void FormulinhaClass::SeguirLinha() { FollowLine(); }
void FormulinhaClass::EvitarLinha() { AvoidLine(); }
void FormulinhaClass::ModoFesta() { PartyMode(); }
void FormulinhaClass::EscolherModo() { ScrollModes(); }
void FormulinhaClass::MovimentoDeFuga(bool arg) { AvoidMovement(arg); }
void FormulinhaClass::EvitarObjeto() { AvoidObject(); }
bool FormulinhaClass::AtacarObjeto(unsigned int arg) { AttackObject(arg); }

FormulinhaClass Formulinha;
