#include "UltrasonicBuzzer.h"

// Definições dos pinos
#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 11
#define LED_PIN 12

// Cria uma instância da classe UltrasonicBuzzer
UltrasonicBuzzer ultrasonicBuzzer(TRIG_PIN, ECHO_PIN, BUZZER_PIN, LED_PIN);

void setup() {
    // Inicializa o sensor e o buzzer
    ultrasonicBuzzer.begin();
}

void loop() {
    // Atualiza a lógica do sensor e buzzer
    ultrasonicBuzzer.update();
}