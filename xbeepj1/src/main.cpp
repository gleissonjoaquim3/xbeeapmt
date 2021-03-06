/* Copyright (C) 2020  Gleisson J. J. Cardoso <gleissoncg2@gmail.com>
 *               2020  Robson Cordeiro  <robson.cordeiro@apmt.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/* Código para que seja enviado um sinal via placa xbee para outro dispositivo xbee
//que ao receber este sinal envia outro como resposta */

#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

SoftwareSerial XBee(2, 3); // RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#define pinbotao 10 // Botão definido na entrada digital 12

boolean estadobotao = false; // Definido estado da variavel estadodobotao tipo verdadeiro ou falsa
boolean estantbotao = false; // Definido estado da variavel estantbotão na variavel tipo verdadeiro ou falsa
boolean pisca = false; // Definido estado da variavel pisca tipo verdadeiro ou falsa
int tela = 1; // Muda estado da tela

void mens_inicial(){
  // Função que mostra mensagen ao ligar o arduino
  lcd.setCursor(3,0);
  lcd.print("CHAMADA VAN");
  lcd.setCursor(4,1);
  lcd.print("Ver. 1.0");
  delay(2000);
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(150);
  }
  for (int posicao = 0; posicao < 10; posicao++)
  {
    lcd.scrollDisplayRight(); //Rolagem para a direita
    delay(150);
  }
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(150);
  }
delay(1000);
lcd.clear();
}

void mens_local(){
  lcd.setCursor(3,0);
  lcd.print("CHAMADA VAN");
  lcd.setCursor(1,1);
  lcd.print("LOCAL - OFICINA");
  delay(300);
}

void mens_chama_van(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("CHAMANDO VAN");
  lcd.setCursor(4,1);
  lcd.print("AGUARDE...");
  lcd.noDisplay();
  delay(500);
  lcd.display();
  delay(500);
}

void mens_a_caminho(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("VAN A CAMINHO");
  delay(12000);
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(200);
  }
  for (int posicao = 0; posicao < 10; posicao++)
  {
    lcd.scrollDisplayRight(); //Rolagem para a direita
    delay(200);
  }
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(100);
  }
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("AGUADE");
  lcd.setCursor(4,1);
  lcd.print("NO LOCAL");
  delay(10000);
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(200);
  }
  for (int posicao = 0; posicao < 10; posicao++)
  {
    lcd.scrollDisplayRight(); //Rolagem para a direita
    delay(200);
  }
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(100);
  }

}

void setup()
{ // Código que será carregado ao ligar o arduino
  lcd.init();
  lcd.backlight();
  pinMode(pinbotao, INPUT); // Variavel pinbotao definida como entrada(INPUT)
  XBee.begin(9600); // Inicia o serial de leitura do xbee no BAUD RATE 9600
  //Serial.begin(9600); // Inicia o serial monitor no BAUD RATE 9600
  mens_inicial();
}

void loop()
{
  // Será repetido infinitamente pelo arduino
  XBee.available();  // Verifica se há algum xbee disponivel
  char c = XBee.read(); // Armazena na variavel c o sinal recebido
  //Serial.print(c);
  estadobotao = digitalRead(pinbotao); // estadobotao recebe o sinal do botão

  if (estadobotao == HIGH) // se o botão for pressionado
  {
    XBee.write('L');
    delay(500); // Manda um caracter 'L' para outro disposisivo
  }

  if (estadobotao && !estantbotao ) // Condição que compara o estado atual com o estado anterior do botão
  {
    pisca = !pisca; // troca o estaco da variavel pisca para true
    tela = 2; // Troca menu da tela
  }
  if (c == 'l' && (pisca)) // Condição caso receba o caracter correto e o pisca for false
  {
    pisca = !pisca;
    tela = 3; //Troca menu da tela
    
  }
  delay(200);

  switch (tela) // Alterna os casos dependendo do valor da variável tela
  {
  case 1:
    mens_local();
    break;
  case 2:
    mens_chama_van();
    break;
  case 3:
  {
    mens_a_caminho();
    delay(120000);
    tela = 1;
    break;
  }
  } 
}
