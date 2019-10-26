#include <Formulinha.h>

void setup()
{
  Formulinha.init();
}
void loop()
{
  // digitalWrite(PIN_GREEN, HIGH);
  // delay(1000);
  // digitalWrite(PIN_GREEN, LOW);
  // delay(1000);

  // digitalWrite(PIN_RED, HIGH);
  // delay(1000);
  // digitalWrite(PIN_RED, LOW);
  // delay(1000);

  // digitalWrite(PIN_BLUE, HIGH);
  // delay(1000);
  // digitalWrite(PIN_BLUE, LOW);
  // delay(1000);
  // //Formulinha.sound(S_HAPPY);
  // delay(1000);
  unsigned int luz = Formulinha.light();
  double distancia = Formulinha.distance();

  Formulinha.updateLineSensors();
  Serial.print(Formulinha.lineSensor[0]);
  Serial.print("\t");
  Serial.print(Formulinha.lineSensor[1]);
  Serial.print("\t");
  Serial.print(Formulinha.lineSensor[2]);
  Serial.print("\t");
  Serial.print(Formulinha.lineSensor[3]);
  Serial.print("\t");
  Serial.print(Formulinha.lineSensor[4]);
  Serial.print("\t");
  Serial.print(luz);
  Serial.print("\n");
  Serial.print(distancia);
  Serial.print(" cm\n");

  // Formulinha.right(100,100);
}
