#include <Thermistor.h> //https://github.com/xreef/Thermistor_library

#define FAN_IN2 4  // Pino de controle da Ventoinha na ponte H
#define FAN_IN1 2  // Pino de controle da Ventoinha na ponte H (carga negativa)
#define SENSOR A0 // Pino analógico conectado ao termistor NTC

Thermistor thermistor(SENSOR);  // Configuração do termistor NTC

void setup() {
  pinMode(FAN_IN1, OUTPUT);
  pinMode(FAN_IN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  float temperatura = thermistor.readTemperature(); //le a temperatura em fahrenheit

  Serial.println(temperatura);

  if (temperatura <= 50) //caso a temperatura seja menor ou igual ao valor no if a ventoinha permanece parada
  {
    digitalWrite(FAN_IN1,LOW);
    digitalWrite(FAN_IN2,LOW);
  } else //caso contrario, a ventoinha girará
  {
    digitalWrite(FAN_IN1,LOW);
    digitalWrite(FAN_IN2,HIGH);
  }

}



