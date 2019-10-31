# Formulinha: Seu Robô Tudo em Um



### Dependencias

Nenhuma.

### Instalação

Você pode baixar o zip e incluir manualmente através da IDE do Arduino ou instalar diretamente pelo gerenciador de bibliotecas

### Exemplo com comandos disponíveis:

#include <Formulinha.h>

void setup()
{
  Formulinha.Iniciar(); //configura todos os pinos do Arduino para um Robô Formulinha
  // Formulinha.LinhaPreta();  //configura para usar linha preta com fundo branco
  // Formulinha.LinhaBranca(); //configura para usar linha branca com fundo preto
  // delay(2000);
  // Formulinha.CalibrarSensorDeLinha(); //calibra os sensores para detectar melhor a ("Farejar a linha")
}
void loop()
{
  // Formulinha.UsarServo();                                //habilita o uso do servo no mesmo pino do led verde
  // Formulinha.RemoverServo();                             //desabilita o servo para não interferir no brilho do led verde
  // Formulinha.Som(S_HAPPY);                               //faz som de feliz. A lista com todos os sons está na documentação da biblioteca
  // Formulinha.AtualizarSensorDeLinha();                   //lê todos os sensores de linha uma unica vez
  // Formulinha.MediaSensorDeLinha();                       //lê os sensores de linha varias vezes e tira uma média para reduzir erros de leitura
  // Formulinha.Frente(100, 100);                           //anda pra frente com 100% da potência do motor esquerdo e 100% da potência do motor direito (Precisa de par de motores DC)
  // Formulinha.Tras(100, 100);                             //anda pra tras com 100% da potência do motor esquerdo e 100% da potência do motor direito (Precisa de par de motores DC)
  // Formulinha.Esquerda(100, 100);                         //gira para a esquerda com 100% da potência do motor esquerdo e 100% da potência do motor direito (Precisa de par de motores DC)
  // Formulinha.Direita(100, 100);                          //gira para a direita com 100% da potência do motor esquerdo e 100% da potência do motor direito (Precisa de par de motores DC)
  // int luzAmbiente = Formulinha.Luz();                    //lê a quantidade de luz ambiente e retorna um valor entre 0 a 1023
  // float distanciaEmCentimetros = Formulinha.Distancia(); //lê a distância entre o robô e um objeto à sua frente (distância mínima de 2 cm e máxima de 4 metros) (precisa de sensor ultrassonico)
  // bool botaoAPressionado = Formulinha.BotaoA();          //verifica se o botão A foi pressionado
  // bool botaoBPressionado = Formulinha.BotaoB();          //verifica se o botão B foi pressionado
  // Formulinha.SeguirLinha();                              //segue linha após executada a calibração (Precisa de par de motores DC)
  // Formulinha.EvitarLinha();                              //evita cruzar linha após executada a calibração (Precisa de par de motores DC)
  // Formulinha.ModoFesta();                                //fica feliz quando estiver escuro e triste quando estiver claro
  // Formulinha.EscolherModo();                             //navega entre modos de operação quando pressionado o boão A
  // Formulinha.EvitarObjeto();                             //evita colidir com objetos a sua frente (precisa de sensor ultrassonico e par de motores DC)
  // bool alvoDetectado = Formulinha.AtacarObjeto(70);      //ataca objetos que entrem em sua frente numa distância de 70 cm (precisa de sensor ultrassonico e par de motores DC)
  // Formulinha.Servo(120);         //Move o servo para a posição de 120 graus (Precisa de Servo 9g)
  // Formulinha.Led(100, 100, 100); //liga o led embaixo do Formulinha com 100% de Vermelho, 100% de Verde e 100% de Azul
  // Formulinha.Sumo();             //evita cruzar linhas e ataca objetos em sua frente (precisa de sensor ultrassonico e par de motores DC)
  // Serial.println("Ola Mundo"); //Escreve no monitor serial a frase "Ola Mundo" com baud rate de 115200
}

### Sons disponíveis:

- **S_CONNECTION**
- **S_DISCONNECTION**
- **S_BUTTON_PUSHED**
- **S_MODE1**
- **S_MODE2**
- **S_MODE3**
- **S_SURPRISE**
- **S_OHOOH**
- **S_OHOOH2**
- **S_CUDDLY**
- **S_SLEEPING**
- **S_HAPPY**
- **S_SUPER_HAPPY**
- **S_HAPPY_SHORT**
- **S_SAD**
- **S_CONFUSED**
- **S_FART1**
- **S_FART2**
- **S_FART3**

