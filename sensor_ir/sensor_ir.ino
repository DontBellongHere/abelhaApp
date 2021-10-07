int pinLed = 12; // led conectado no pino digital 12
int pinSensor = 2; // módulo conectado no pino digial 2
int pinSensorAnalogico = A0; // módulo conectado no pino analógico A0
   
void setup(){ 
  Serial.begin(9600);
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
}
