#include <Formulinha.h>

void setup()
{
  Formulinha.Iniciar();
  Formulinha.LinhaPreta();
  delay(2000);
  Formulinha.CalibrarSensorDeLinha();
}
void loop()
{
  Formulinha.SeguirLinha();
}