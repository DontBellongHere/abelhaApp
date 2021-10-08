
#include "dht.h" //INCLUSÃO DE BIBLIOTECA
 
const int pinoDHT11 = A1; //PINO ANALÓGICO UTILIZADO PELO DHT11
 
dht DHT; //VARIÁVEL DO TIPO DHT

int pinLed = 12; // led conectado no pino digital 12
int pinSensor = 2; // módulo conectado no pino digial 2
int pinSensorAnalogico = A0; // módulo conectado no pino analógico A0
 
void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(1000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR

  pinMode(pinSensor, INPUT); // define como entrada
  pinMode(pinLed, OUTPUT); // definoe como saída   
  digitalWrite(pinLed, LOW); // led incia apagado
}
 
void loop(){

  Serial.println(analogRead(pinSensorAnalogico));
  if (digitalRead(pinSensor) == LOW){ // se for LOW 
        digitalWrite(pinLed, HIGH); // acende o led
  } else { // caso contrário
        digitalWrite(pinLed, LOW); // apaga o led
  }   

  
  DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.humidity); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
} 
