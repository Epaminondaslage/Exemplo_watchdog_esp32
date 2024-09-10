/*

Usa o ESP32 WROOM -DA 

inclui a biblioteca ESP Task Watchdog Timer que permite o uso do watchdog no ESP32. 
Essa biblioteca faz parte do ESP-IDF e está disponível automaticamente quando o pacote ESP32 é instalado
no Arduino IDE.

O Watchdog Timer é usado para garantir que o sistema seja reiniciado automaticamente em caso de travamento.
O código reseta o WDT regularmente, e se esse reset não ocorrer dentro do tempo limite
(simulado com delay(6000)), o ESP32 será reiniciado.

*/

#include <esp_task_wdt.h>  // Biblioteca para Watchdog Timer no ESP32

// Defina o tempo limite do Watchdog (em segundos)
#define WDT_TIMEOUT 5  // Tempo limite de 5 segundos

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Inicializando Watchdog Timer...");

  // Inicializa o Watchdog Timer com a estrutura de configuração
  esp_task_wdt_config_t wdtConfig = {
    .timeout_ms = WDT_TIMEOUT * 1000,  // Tempo limite em milissegundos
  };

  esp_task_wdt_init(&wdtConfig);  // Inicializa o WDT com a configuração
  esp_task_wdt_add(NULL);  // Adiciona a tarefa principal ao Watchdog
}

void loop() {
  // Simulação de tarefa que roda corretamente
  for (int i = 0; i < 5; i++) {
    Serial.println("Loop executando normalmente...");
    delay(1000);  // Delay de 1 segundo
  }


  // Reseta o Watchdog Timer para evitar o reinício
  esp_task_wdt_reset();

  // Simula um travamento (não reseta o WDT por 6 segundos)
  Serial.println("Simulando um travamento...");
  delay(6000);  // Tempo maior que o limite do Watchdog
}
