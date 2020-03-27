/* Código para que seja enviado um sinal via placa xbee para outro dispositivo xbee
//que ao receber este sinal envia outro como resposta */

/* Ponto Abrigo da Van*/

#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4); // Setup do lcd

SoftwareSerial XBee(2, 3); // RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#define pinbotao 10 // Botão definido na entrada digital 12
#define ledvm 9 // LED definido na saída digital 7
#define ledvd 8 // LED definido na saída digital 6

boolean estadobotao = false; // Definido estado da variavel estadodobotao tipo verdadeiro ou falsa
boolean estantbotao = false; // Definido estado da variavel estantbotão na variavel tipo verdadeiro ou falsa
boolean pisca = false; // Definido estado da variavel pisca tipo verdadeiro ou falsa
unsigned long delay1 = 0; // Definido variavel delay1 com início em 0
// tipo de declaração que pode armazenar maior quantidade de números

  /***************************************************
  * Função que gera pulso (1º argum, variavel a ser pulsada, 2º
  argum, tempo de duração do pulso em millisegundo)
  ****************************************************/
void pulso(int pino, unsigned int tempo)
{
  if ((millis() - delay1) >= tempo) //Função millis Retorna o número de milissegundos passados desde
    {                                  //que a placa Arduino começou a executar o programa atual.
                                    // Se a diferença entre a condição for maior ou igual a x. Executa algo
      digitalWrite( pino, HIGH); // Acende o led vermelho
    }
    if ((millis() - delay1) < tempo) //Se a diferença entre a condição for menor a x. Executa algo
    {
      digitalWrite( pino, LOW); // Apaga o led vermelho.
    }
    if ((millis() - delay1) >= (tempo*2))
    {
      delay1 = millis(); // Faz com que a função millis retorne ao valor 0
    }
}

void movimento (){
  for (int posicao = 0; posicao < 2; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 4; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
  for (int posicao = 0; posicao < 2; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

void home(){
  lcd.setCursor(2,0);
  lcd.print("Pondo da Van");
  lcd.setCursor(2,1);
  lcd.print("Abrigo - 01");
}


void setup()
{ // Código que será carregado ao ligar o arduino
  lcd.init();
  lcd.backlight();
  home();
  pinMode(pinbotao, INPUT); // Variavel pinbotao definida como entrada(INPUT)
  //pinMode(LED_BUILTIN,OUTPUT);
  pinMode(ledvd,OUTPUT); // Variavel ledvd definida como entrada(OUTPUT)
  pinMode(ledvm,OUTPUT); // Variavel ledvd definida como entrada(OUTPUT)
  XBee.begin(9600); // Inicia o serial de leitura do xbee no BAUD RATE 9600
  Serial.begin(9600); // Inicia o serial monitor no BAUD RATE 9600
  lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Transporte");
    lcd.setCursor(3,1);
    lcd.print("a caminho ! "); // Escreve no lcd
    movimento();
}

void loop()
{ // Será repetido infinitamente pelo arduino
  //Rolagem para a esquerda
  lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Transporte");
    lcd.setCursor(3,1);
    lcd.print("a caminho ! "); // Escreve no lcd
    movimento();
    delay(5000);
    home();
  XBee.available();  // Verifica se há algum xbee disponivel
  char c = XBee.read(); // Armazena na variavel c o sinal recebido
  //Serial.print(c);
  estadobotao = digitalRead(pinbotao); // estadobotao recebe o sinal do botão
  //Serial.print(estadobotao);

  if (estadobotao == HIGH) // se o botão for pressionado
  {
    XBee.write('A');
    delay(500); // Manda um caracter 'L' para outro disposisivo
  }

  if (estadobotao && !estantbotao ) // Condição que compara o estado atual com o estado anterior do botão
  {
    pisca = !pisca; // troca o estaco da variavel pisca para true
  }

  if (c == 'a') // Condição caso receba o caracter correto e o pisca for false
  {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Transporte");
    lcd.setCursor(3,1);
    lcd.print("a caminho ! "); // Escreve no lcd
    delay(12000);
    movimento();
    home();
  }
   // Aqui digo que caso o botao seja acionado entrará em modo de pisca
  if (pisca ) // se a variavel pisca for true
  {
    pulso(ledvm,700);
  }
  else
  {
    home();
  }

delay(200);
}
