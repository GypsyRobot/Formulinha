#include <Formulinha.h>

void setup()
{
  Formulinha.Iniciar();
  Formulinha.LinhaPreta();
  delay(2000);
  Formulinha.CalibrarSensorDeLinha();
  delay(2000);
}
void loop()
{
  Formulinha.Sumo();
}