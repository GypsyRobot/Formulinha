#include <Formulinha.h>

void setup()
{
  Formulinha.init();
}
void loop()
{
  digitalWrite(PIN_GREEN, HIGH);
  delay(1000);
  digitalWrite(PIN_GREEN, LOW);
  delay(1000);

  digitalWrite(PIN_RED, HIGH);
  delay(1000);
  digitalWrite(PIN_RED, LOW);
  delay(1000);

  digitalWrite(PIN_BLUE, HIGH);
  delay(1000);
  digitalWrite(PIN_BLUE, LOW);
  delay(1000);
  //Formulinha.playSound(S_HAPPY);
  delay(1000);
}
