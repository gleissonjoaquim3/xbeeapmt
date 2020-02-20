/* Programa destinado ao recebimento de sinal que será emitido
pelos postos remotos localizados ao longo do Terminal Portuário */

#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca

SoftwareSerial XBee(2, 3); // Criação do objeto XBee

int pinbotao_1  = 5;  //Definição do botão no pino 5
//#define pinbotao_2 6
//#define pinbotao_3 7
int ledvm1 = 8;    //Definição do botão no pino 8
//#define ledvm2 9
//#define ldevm3 10

int estadobotao_1 = 0;  //Estado atual do botão
//int estadobotao_2 = 0;  //Estado atual do botão
//int estadobotao_3 = 0;  //Estado atual do botão

/***************************************************
* Função que pega a letra recebida pelo xbee e manda o
mesmo caracter como retorno.
letra_a_receber = string recebida pelo XBee
letra_a_enviar = envia de volta um string
led = led para acionar na saída
botao = botão que será acionado
estadobotao = faz a leitura do estado do botão
****************************************************/

void setup() // Código carregado apenas uma vez.
{

  Serial.begin(9600);
  XBee.begin(9600);
  pinMode(pinbotao_1, INPUT);
  pinMode(ledvm1, OUTPUT);
  //pinMode(ledvm2, OUTPUT);
  //pinMode(ledvm3, OUTPUT);
}

void loop() // Código qe será executado sempre pelo arduino
{
  estadobotao_1 = digitalRead(pinbotao_1);

  XBee.available();
  char c = XBee.read();
  //Serial.print(c);

  if (c == 'K')
  {
    digitalWrite(ledvm1, HIGH);
  }

  if (estadobotao_1 == HIGH)
  {
    XBee.write('k');
    delay(500);
    digitalWrite(ledvm1, LOW);
  }
  }
