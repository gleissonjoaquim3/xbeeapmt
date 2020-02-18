#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca

SoftwareSerial XBee(2, 3); // Criação do objeto XBee

#define pinbotao_1 5  //Definição do botão no pino 5
#define pinbotao_2 6
#define pinbotao_3 7
#define ledvm1 8    //Definição do botão no pino 8
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
void pega_caracter(const char letra_a_receber,
    const char letra_a_enviar,
    int led, int botao,
    int estadobotao)
{
XBee.available(); // Verifica a disponibilidade de outros dispositivos
char c = XBee.read(); // Faz a leitura de sinal enviado
//XBee.print(c); // Descomentar para ver pelo serial o sinal recebido

estadobotao = digitalRead(botao); // Recebe o sinal do botao

if (c == letra_a_receber)
{
  digitalWrite(led, HIGH); // Aciona o led

  if (estadobotao == HIGH)
  {
    XBee.write(letra_a_enviar); // Escreve na saida xbee
    digitalWrite(led, LOW); // Desliga o led
  }

/*TODO Estudar uma forma de fazer um tipo de envio que possa "buscar"
o outro dispositivo */

}


}

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

pega_caracter('K', 'k', ledvm1, pinbotao_1, estadobotao_1);

}
