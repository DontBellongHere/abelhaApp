/* AUTOR:     BrincandoComIdeias
*  ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
*  APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
*  COMPRE:    https://www.arducore.com.br/
*/
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
DHT dht(DHTPIN, DHTTYPE);

//******* CONFIGURACAO DO PROJETO *********
#define pinBotoes A0

#define pinRs 8
#define pinEn 9
#define pinD4 4
#define pinD5 5
#define pinD6 6
#define pinD7 7
#define pinBackLight 10
//*****************************************

#define btNENHUM 0
#define btSELECT 1
#define btLEFT   2
#define btUP     3
#define btDOWN   4
#define btRIGHT  5

#define tempoDebounce 50

unsigned long delayBotao;
int estadoBotaoAnt = btNENHUM;

void estadoBotao(int botao);
void botaoApertado(int botao);
void botaoSolto(int botao);

LiquidCrystal lcd(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);

//Para o exemplo de uso
String descBotao[6] = {"", "Select", "Esquerda", "Abaixo", "Acima", "Direita"};
int contador = 0;
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};
void setup() {
  pinMode(pinBackLight, OUTPUT);
  digitalWrite(pinBackLight, HIGH);
  //Cria o caractere customizado com o simbolo do grau
  lcd.createChar(0, grau);
  lcd.begin(16, 2);
  Serial.begin(9600);
   dht.begin();
}

void loop() {
  int valBotoes = analogRead(pinBotoes);

  if ((valBotoes < 800) && (valBotoes >= 600)) {
     estadoBotao(btSELECT);
     
  } else if ((valBotoes < 600) && (valBotoes >= 400)) {
     estadoBotao(btLEFT);
     
  } else if ((valBotoes < 400) && (valBotoes >= 200)) {
     estadoBotao(btUP);
     
  } else if ((valBotoes < 200) && (valBotoes >= 60)) {
     estadoBotao(btDOWN);
     
  } else if  (valBotoes < 60) {
     estadoBotao(btRIGHT);
     
  } else {
     estadoBotao(btNENHUM);
  }
}

void estadoBotao(int botao) {
  //Quando um botao estiver apertado
  if (botao == btNENHUM) {
     float h = dht.readHumidity(); //Le o valor da umidade
     float t = dht.readTemperature(); //Le o valor da temperatura
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     lcd.print(" ");
     lcd.setCursor(7,0);
     lcd.print(t,1);
     lcd.setCursor(12,0);

//Mostra o simbolo do grau formado pelo array
lcd.write((byte)0);

//Mostra o simbolo do grau quadrado
//lcd.print((char)223);

lcd.setCursor(0,1);
lcd.print("Umid : ");
lcd.print(" ");
lcd.setCursor(7,1);
lcd.print(h,1);
lcd.setCursor(12,1);
lcd.print("%");

//Intervalo recomendado para leitura do sensor
delay(2000);
     Serial.println(botao);
  }

  //Quando o botao for apertado ou solto
  if ((millis() - delayBotao) > tempoDebounce) {
     if ((botao != btNENHUM) && (estadoBotaoAnt == btNENHUM) ) {
        botaoApertado(botao); 
        delayBotao = millis();
     }

     if ((botao == btNENHUM) && (estadoBotaoAnt != btNENHUM) ) {
        botaoSolto(estadoBotaoAnt); 
        delayBotao = millis();
     }
  }
  estadoBotaoAnt = botao;
}

void botaoApertado(int botao) {
  //Quando um botão for apertado

  //Para o exemplo de uso
  contador++;
  lcd.clear();
  lcd.print(descBotao[botao]);
  lcd.setCursor(14,0);
  lcd.print(contador);
  lcd.setCursor(0,1);
  lcd.print("luciano");
}

void botaoSolto(int botao) {
  //Quando um botão for solto


  //Para o exemplo de uso
  lcd.clear();
  lcd.print(descBotao[botao]);
  lcd.setCursor(14,0);
  lcd.print(contador);
  lcd.setCursor(0,1);
  lcd.print("solto");
}
