/* Output-side (LED) Arduino code */
#include <SoftwareSerial.h>
#include <Arduino.h>
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
const int LED1 = 9;  //Declaração do led1 no pino 9
//const int LED2 = 10; //Declaração do led2 no pino 10
//const int LED3 = 11; //Declaração do led3 no pino 11
const int bto1 = 8;  //Declaração do bot1 no pino 8
//const int bto2 = 7;  //Declaração do bot2 no pino 7
//const int bto3 = 6;  //Declaração do bot3 no pino 6
int estadobot1 = 0;
//int estadobot1 , estadobot2 , estadobot3 = 0; //Variável que conterá os estados do botão (0 LOW, 1 HIGH).


void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(LED1,OUTPUT); //Led 1 configurado como saída
  //pinMode(LED2,OUTPUT); //Led 2 configurado como saída
  //pinMode(LED3,OUTPUT); //Led 3 configurado como saída
  pinMode(bto1,INPUT); //bto1 configurado como entrada
  //pinMode(bto2,INPUT); //bto2 configurado como entrada
  //pinMode(bto3,INPUT); //bto3 configurado como entrada
}

void loop()
{
  //Faz a leitura do estado do pino 2, constante botao, e atribuindo 
  //o resultado a variável estadoBotao.
  estadobot1 = digitalRead(bto1);
  //estadobot2 = digitalRead(bto2);
  //estadobot3 = digitalRead(bto3);    

  if (XBee.available())  //Verifica se tem outros xbee disponiveis
  { 
    char c = XBee.read(); // Faz a leitura enviada por outro xbee
    
    if (c == 'H' && estadobot1 == LOW) //Caso receba a letra H e o botão não esteja pressuinado
    {
      digitalWrite(LED1, HIGH); // Acende o led
      Serial.print("Chamada berço 1"); // No Seria monitor printa a Identificação do berço 1 por exemplo
      delay (1000);
      digitalWrite(LED1,LOW);
      delay(1000); // Delay de 4s
    }
    else
    {
    digitalWrite(LED1, LOW);
    XBee.write("R");
    }
    
  }
  
}
  
