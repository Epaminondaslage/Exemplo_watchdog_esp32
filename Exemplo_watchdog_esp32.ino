/*

Usa o ESP32 WROOM-DA 

inclui a biblioteca ESP Task Watchdog Timer que permite o uso do watchdog no ESP32. 
Essa biblioteca faz parte do ESP-IDF e está disponível automaticamente quando o pacote ESP32 é instalado
no Arduino IDE.

O Watchdog Timer é usado para garantir que o sistema seja reiniciado automaticamente em caso de travamento.
O código reseta o WDT regularmente, e se esse reset não ocorrer dentro do tempo limite
(simulado com delay(6000)), o ESP32 será reiniciado.
*/

// Biblioteca para Watchdog Timer no ESP32
#include <esp_task_wdt.h>  

// Defina o pino do LED embutido no ESP32
#define LED_PIN 2  // Pino do LED embutido no ESP32 (geralmente é o pino 2)

// Defina o tempo limite do Watchdog (em segundos)
#define WDT_TIMEOUT 5  // Tempo limite de 5 segundos

void setup() {

 // Configura o LED embutido como saída
  pinMode(LED_PIN, OUTPUT);

  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Inicializando Watchdog Timer...");

  // Inicializa o Watchdog Timer com a estrutura de configuração
  esp_task_wdt_config_t wdtConfig = {
    .timeout_ms = WDT_TIMEOUT * 1000,  // Tempo limite em milissegundos
  };
  // Inicializa o WDT com a configuração
  esp_task_wdt_init(&wdtConfig);  
  esp_task_wdt_add(NULL);  // Adiciona a tarefa principal ao Watchdog
}

void loop() {

  // Simulação de tarefa que roda corretamente
  
  for (int i = 0; i < 5; i++) {
  Serial.print("Loop executando normalmente, valor de i: ");
  Serial.println(i);  // Exibe o valor da variável i
  // Acende o LED
  digitalWrite(LED_PIN, HIGH);
  delay(500);  // Mantém o LED aceso por 500ms

  // Apaga o LED
  digitalWrite(LED_PIN, LOW);
  delay(500);  // Mantém o LED apagado por 500ms
}

  // Reseta o Watchdog Timer para evitar o reinício
  esp_task_wdt_reset();

  // Simula um travamento (não reseta o WDT por 6 segundos)
  Serial.println("Simulando um travamento...");
  delay(6000);  // Tempo maior que o limite do Watchdog
}
