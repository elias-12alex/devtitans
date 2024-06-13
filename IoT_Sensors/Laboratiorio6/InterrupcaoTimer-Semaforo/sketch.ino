/*
  DevTITANS
  Atividade 4 - Semaforo
  @Elias Alexander
  @Aris Canto
*/

#define LED_CARROS_VERDE 32
#define LED_CARROS_AMARELO 33
#define LED_CARROS_VERMELHO 25
#define LED_PEDESTRES_VERDE 26
#define LED_PEDESTRES_VERMELHO 27
#define BOTAO_PEDRESTRES 2

hw_timer_t * timer = NULL; 
volatile bool timerInterrupt = false;
volatile bool botaoPressionado = false;
//bool estadoLEDs[5] = {true, false, false, false, true}; // [LED_CARROS_VERDE, LED_CARROS_AMARELO, LED_CARROS_VERMELHO, LED_PEDESTRES_VERDE, LED_PEDESTRES_VERMELHO]
unsigned long tempoAnterior = 0; // Para controlar os tempos sem usar delay()
int estadoAtual = 0; // 0 - carros verdes, 1 - carros amarelos, 2 - carros vermelhos, 3 - pedestres verdes, 4 - pedestres vermelhos

void IRAM_ATTR onTimer() {
  timerInterrupt = true;
}

void IRAM_ATTR botaoPressed() {
  botaoPressionado = true;
}

void mudarEstado(int novoEstado) {
  Serial.print("Mudando para estado ");
  Serial.println(novoEstado);
  digitalWrite(LED_CARROS_VERDE, novoEstado == 0 || novoEstado == 3);
  digitalWrite(LED_CARROS_AMARELO, novoEstado == 1);
  digitalWrite(LED_CARROS_VERMELHO, novoEstado == 2);
  digitalWrite(LED_PEDESTRES_VERDE, novoEstado == 2);
  digitalWrite(LED_PEDESTRES_VERMELHO, novoEstado == 0 || novoEstado == 3);
  estadoAtual = novoEstado; // Atualizar o estado atual após a mudança
}

void setup() {
  pinMode(LED_CARROS_VERDE, OUTPUT);
  pinMode(LED_CARROS_AMARELO, OUTPUT);
  pinMode(LED_CARROS_VERMELHO, OUTPUT);
  pinMode(LED_PEDESTRES_VERDE, OUTPUT);
  pinMode(LED_PEDESTRES_VERMELHO, OUTPUT);
  pinMode(BOTAO_PEDRESTRES, INPUT_PULLUP);
  
  Serial.begin(115200);

  // Configurar interrupção para o timer
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true); 
  timerAlarmWrite(timer, 1000000, true); // 1 segundo
  timerAlarmEnable(timer);

  // Configurar interrupção para o botão de pedestres
  attachInterrupt(digitalPinToInterrupt(BOTAO_PEDRESTRES), &botaoPressed, FALLING);

  // Inicializar semáforos
  mudarEstado(0); // Começar com carros verdes e pedestres vermelhos
}

void loop() {
  if (timerInterrupt) {
    timerInterrupt = false;
    unsigned long currentMillis = millis();

    switch (estadoAtual) {
      case 0:
        if (botaoPressionado) {
          botaoPressionado = false;
          mudarEstado(1);
          tempoAnterior = currentMillis;
        }
        break;
      case 1:
        if (currentMillis - tempoAnterior >= 1000) { // 1 segundo
          mudarEstado(2);
          tempoAnterior = currentMillis;
        }
        break;
      case 2:
        if (currentMillis - tempoAnterior >= 2000) { // 2 segundos
          mudarEstado(3);
          tempoAnterior = currentMillis;
        }
        break;
      case 3:
        if (currentMillis - tempoAnterior >= 2000) { // simbolicamente 2 segundos, mas representa o estado inicial
          mudarEstado(0);
        }
        break;
    }
  }

}
