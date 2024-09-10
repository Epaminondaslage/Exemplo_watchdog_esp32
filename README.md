# Exemplo de uso de watchdog no ESP32
 
A função esp_task_wdt_reset() deve ser chamada periodicamente dentro do loop principal para "alimentar" o Watchdog Timer e evitar que ele reinicie o sistema. O local específico onde você deve colocar essa função depende de como o código está estruturado e quais partes podem potencialmente travar.

Aqui estão algumas diretrizes sobre onde colocar o esp_task_wdt_reset():
1. Dentro de loops ou tarefas demoradas:

Se o seu código contém loops ou tarefas que podem demorar mais do que o tempo limite do watchdog para serem concluídas, você deve chamar esp_task_wdt_reset() dentro dessas tarefas ou após elas, garantindo que o watchdog seja alimentado antes que o tempo limite seja excedido.

Exemplo:

```
void loop() {
  // Simulação de tarefa que roda corretamente
  for (int i = 0; i < 5; i++) {
    Serial.println("Loop executando normalmente...");
    delay(1000);  // Delay de 1 segundo
  }

  // Reseta o Watchdog Timer após o loop demorado
  esp_task_wdt_reset();  // Alimenta o WDT para evitar o reinício do sistema

  // Outra tarefa que pode demorar
  longTask();

  // Reseta o Watchdog Timer novamente
  esp_task_wdt_reset();  // Alimenta o WDT após a tarefa longa
}

void longTask() {
  // Simula uma tarefa que demora muito
  for (int i = 0; i < 10; i++) {
    Serial.println("Tarefa longa em execução...");
    delay(500);  // Cada ciclo desta tarefa demora 500 ms
  }
}

```

Nesse exemplo, o esp_task_wdt_reset() é chamado após o loop principal e após a tarefa longTask(), garantindo que o WDT seja alimentado regularmente.
2. No final do loop():

Se o código dentro do loop() for relativamente simples e sem grandes tarefas demoradas, você pode chamar esp_task_wdt_reset() no final de cada ciclo do loop. Isso garante que o Watchdog Timer seja alimentado a cada iteração do loop.

Exemplo:

cpp

void loop() {
  // Código que roda a cada ciclo do loop
  Serial.println("Loop executando normalmente...");
  delay(1000);  // Simulação de uma tarefa leve com delay

  // Alimenta o Watchdog Timer no final do loop
  esp_task_wdt_reset();  // Alimenta o WDT a cada iteração do loop
}

3. Em pontos críticos:

Se você tiver pontos específicos no seu código que possam causar travamentos (por exemplo, chamadas de rede, tarefas com bloqueios, ou funções que dependem de hardware), é recomendado chamar o esp_task_wdt_reset() após essas seções de código.

Exemplo:

cpp

void loop() {
  // Simulação de uma tarefa normal
  Serial.println("Loop executando normalmente...");
  delay(1000);  // Simulação de uma tarefa leve com delay

  // Ponto crítico onde pode ocorrer travamento
  performNetworkTask();

  // Alimenta o Watchdog Timer após o ponto crítico
  esp_task_wdt_reset();  // Alimenta o WDT após a tarefa potencialmente problemática
}

void performNetworkTask() {
  // Simula uma tarefa de rede que pode demorar ou travar
  Serial.println("Executando tarefa de rede...");
  delay(3000);  // Simula uma tarefa que pode demorar (3 segundos)
}

Resumo:

    Chame esp_task_wdt_reset() após qualquer tarefa que possa demorar ou causar bloqueio (como loops demorados, comunicação com hardware ou rede).
    Posicione esp_task_wdt_reset() no final do loop() para garantir que o WDT seja alimentado em todas as iterações.
    Evite chamar esp_task_wdt_reset() com muita frequência em tarefas muito rápidas, pois isso pode mascarar problemas de desempenho (o watchdog só deve ser alimentado quando o código está rodando corretamente).

Dessa forma, você protege o sistema contra travamentos e reinicializações desnecessárias, mantendo o código fluindo normalmente.
