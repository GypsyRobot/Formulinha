#ifndef Formulinha_h
#define Formulinha_h
#ifdef __AVR__
#include <avr/power.h>
#endif
#define debug true

#include <Servo.h>
#include <CuteBuzzerSounds.h>

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

  bool lineLost = false;
  bool avoidSide = false;

  void init();
  void useServo();
  void removeServo();
  void sound(unsigned short);
  void updateLineSensors();
  void averageLineSensors();
  void forward(unsigned short, unsigned short);
  void backward(unsigned short, unsigned short);
  void left(unsigned short, unsigned short);
  void right(unsigned short, unsigned short);
  unsigned int light();
  float distance();
  void led(unsigned short, unsigned short, unsigned short);

  bool buttonA();
  bool buttonB();

  void servo(unsigned short);

  void calibrateLineSensors(bool);

  void followLine(unsigned short, unsigned short);
  void avoidLine();

private:
};

extern FormulinhaClass Formulinha;

#endif
