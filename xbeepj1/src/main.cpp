/* Código para que seja enviado um sinal via placa xbee para outro dispositivo xbee
//que ao receber este sinal envia outro como resposta */

#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca

SoftwareSerial XBee(2, 3); // RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#define pinbotao 12 // Botão definido na entrada digital 12
#define ledvm 7 // LED definido na saída digital 7
#define ledvd 6 // LED definido na saída digital 6

boolean estadobotao = false; // Definido estado da variavel estadodobotao tipo verdadeiro ou falsa
boolean estantbotao = false; // Definido estado da variavel estantbotão na variavel tipo verdadeiro ou falsa
boolean pisca = false; // Definido estado da variavel pisca tipo verdadeiro ou falsa
unsigned long delay1 = 0; // Definido variavel delay1 com início em 0
// tipo de declaração que pode armazenar maior quantidade de números  

void setup()
{ // Código que será carregado ao ligar o arduino
  pinMode(pinbotao, INPUT); // Variavel pinbotao definida como entrada(INPUT)
  //pinMode(LED_BUILTIN,OUTPUT); 
  pinMode(ledvd,OUTPUT); // Variavel ledvd definida como entrada(OUTPUT)
  pinMode(ledvm,OUTPUT); // Variavel ledvd definida como entrada(OUTPUT)
  XBee.begin(9600); // Inicia o serial de leitura do xbee no BAUD RATE 9600
  //Serial.begin(9600); // Inicia o serial monitor no BAUD RATE 9600
}

void loop()
{ // Será repetido infinitamente pelo arduino
  XBee.available();  // Verifica se há algum xbee disponivel
  char c = XBee.read(); // Armazena na variavel c o sinal recebido
  //Serial.print(c);
  estadobotao = digitalRead(pinbotao); // estadobotao recebe o sinal do botão
  
  if (estadobotao == HIGH) // se o botão for pressionado
  {
    XBee.write('K'); // Manda um caracter 'L' para outro disposisivo
  } 

  if (estadobotao && !estantbotao ) // Condição que compara o estado atual com o estado anterior do botão
  {
    pisca = !pisca; // troca o estaco da variavel pisca para true
  }
  
  if (c == 'k' && (pisca)) // Condição caso receba o caracter correto e o pisca for false
  {
    pisca = !pisca;
    digitalWrite(ledvm,LOW);
    digitalWrite(ledvd,HIGH);
    delay(40000);
    digitalWrite(ledvd,LOW); // Acende o led verde por x segundos e apaga o led vermelho

  }
  
   // Aqui digo que caso o botao seja acionado entrará em modo de pisca
  if (pisca ) // se a variavel pisca for true
  
  {      
    if ((millis() - delay1) >= 700) //Função millis Retorna o número de milissegundos passados desde 
    {                                  //que a placa Arduino começou a executar o programa atual.
                                      // Se a diferença entre a condição for maior ou igual a x. Executa algo 
      digitalWrite( ledvm, HIGH); // Acende o led vermelho
    }

    if ((millis() - delay1) < 700) //Se a diferença entre a condição for menor a x. Executa algo 
    {
      digitalWrite( ledvm, LOW); // Apaga o led vermelho.
    }
    
    if ((millis() - delay1) >= 1400)
    {
      delay1 = millis(); // Faz com que a função millis retorne ao valor 0
    }

  } 
  else 
  {
    digitalWrite( ledvm, LOW);
  }
    
delay(200);
}