#include <Formulinha.h>

void setup()
{
  Formulinha.Iniciar();
  Formulinha.LinhaPreta();
  Formulinha.CalibrarSensorDeLinha();
}
void loop()
{
  Formulinha.Sumo();
}