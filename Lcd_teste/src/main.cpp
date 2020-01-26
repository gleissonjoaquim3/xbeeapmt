#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // //Define os pinos que serão utilizados para ligação ao display

int bt = 8; // Defini a entrada do botão
bool estado_botao = false;
bool troca = false;
bool cham = false;


void setup() {

lcd.begin(20,2); //Define o número de colunas e linhas do LCD
Serial.begin(9600); // Inicia o serial monitor
pinMode(bt, INPUT); // Defini o pino como entrada
pinMode(LED_BUILTIN,OUTPUT); // Defini o led interno como saída
lcd.setCursor(3,0);
lcd.print("Sistema de van");
lcd.setCursor(4,1);
lcd.print("Version 1.20v");
delay(5000);
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
delay(2000);
lcd.clear();

}

void loop() {

estado_botao = digitalRead(bt);

if (estado_botao == LOW); 
{
  cham = cham;
  if (cham)
  {
    lcd.setCursor(3,0);
    lcd.print("Aguardando");
    lcd.setCursor(5,1);
    lcd.print("Chamado");
    
  }

}



}