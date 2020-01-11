/* Output-side (LED) Arduino code */
#include <SoftwareSerial.h>
#include <Arduino.h>
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
const int LED = 9; //Declaração do led no pino 9
const int bto = 8;

int estadobot = 0; //Variável que conterá os estados do botão (0 LOW, 1 HIGH).


void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(bto,INPUT);
}

void loop()
{
  //Faz a leitura do estado do pino 2, constante botao, e atribuindo 
  //o resultado a variável estadoBotao.
  estadobot = digitalRead(bto);    

  if (XBee.available())  //Verifica se tem outros xbee disponiveis
  { 
    char c = XBee.read(); // Faz a leitura enviada por outro xbee
    if (c == 'H' && estadobot == LOW) //Caso receba a letra H e o botão não esteja pressuinado
    {
      digitalWrite(LED, HIGH);
      delay(50);
    }
    else
    {
      digitalWrite(LED, LOW);
    }
  }
  else
  {
    Serial.print("Xbee não estão visiveis"); // Manda no monitor serial caso não consiga cominucação
    delay(2000);
  }
  
}
