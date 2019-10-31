#ifndef Formulinha_h
#define Formulinha_h
#ifdef __AVR__
#include <avr/power.h>
#endif
#define debug true

#include <Servo.h>
#include "Arduino.h"
#include "CuteBuzzerSounds.h"

//############# PINOS #############
#define PIN_BUT_A 8
#define PIN_BUT_B 7

#define PIN_LINE_0 A4
#define PIN_LINE_1 A3
#define PIN_LINE_2 A2
#define PIN_LINE_3 A1
#define PIN_LINE_4 A0

#define PIN_LDR A5

#define PIN_RED 11
#define PIN_GREEN 10
#define PIN_BLUE 13

#define PIN_BUZZER 6

#define PIN_MOTOR_A1 4
#define PIN_MOTOR_A2 5
#define PIN_MOTOR_B1 9
#define PIN_MOTOR_B2 12

#define PIN_SERVO 10

#define PIN_ULTRASONIC_ECHO 3
#define PIN_ULTRASONIC_TRIGGER 2

#define SAMPLES_PER_SENSOR 100
#define SAMPLES_PER_AVERAGE 10
#define CALIBRATE_READING_DELAY 120

class FormulinhaClass
{
public:
  Servo myServo;
  unsigned short lineSensor[5];
  unsigned short lineSensorMin[5];
  unsigned short lineSensorMax[5];
  unsigned short lineSensorMed[5] = {500, 500, 500, 500, 500};
  unsigned short lineSensorSamples[5][SAMPLES_PER_SENSOR];
  unsigned short lineSensorMovingAverage[5];
  unsigned short lineSensorMovingAverageSamples[5][10];

  unsigned short speedLeft = 0;
  unsigned short speedRight = 0;

  unsigned short currentMode = 0;

  bool whiteLine = false;

  bool lineLost = false;
  bool avoidSide = false;
  bool genericFlag = false;

  void Start();
  void WhiteLine();
  void BlackLine();
  void UseServo();
  void RemoveServo();
  void Sound(unsigned short);
  void UpdateLineSensors();
  void AverageLineSensors();
  void Forward(unsigned short, unsigned short);
  void Backward(unsigned short, unsigned short);
  void Left(unsigned short, unsigned short);
  void Right(unsigned short, unsigned short);
  unsigned int Light();
  float Distance();
  void Led(unsigned short, unsigned short, unsigned short);

  bool ButtonA();
  bool ButtonB();

  void Servo(unsigned short);

  void CalibrateLineSensors();

  void FollowLine();
  void AvoidLine();

  void PartyMode();

  void ScrollModes();

  void AvoidMovement(bool);
  void AvoidObject();
  bool AttackObject(unsigned int);
  void Sumo();



  void Iniciar();
  void LinhaBranca();
  void LinhaPreta();
  void UsarServo();
  void RemoverServo();
  void Som(unsigned short);
  void AtualizarSensorDeLinha();
  void MediaSensorDeLinha();
  void Frente(unsigned short, unsigned short);
  void Tras(unsigned short, unsigned short);
  void Esquerda(unsigned short, unsigned short);
  void Direita(unsigned short, unsigned short);
  unsigned int Luz();
  float Distancia();
  bool BotaoA();
  bool BotaoB();
  void CalibrarSensorDeLinha();
  void SeguirLinha();
  void EvitarLinha();
  void ModoFesta();
  void EscolherModo();
  void MovimentoDeFuga(bool);
  void EvitarObjeto();
  bool AtacarObjeto(unsigned int);

private:
};

extern FormulinhaClass Formulinha;

#endif
