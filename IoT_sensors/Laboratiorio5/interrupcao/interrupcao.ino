#define LED 32
#define pinoLDRLow 2
#define pinoLDRHigh 4

volatile bool estadoAnterior = LOW; // Inicialmente, o estado do LED é desligado

void IRAM_ATTR turnLEDOn_ISR()
{
  digitalWrite(LED,HIGH);
}

void IRAM_ATTR turnLEDOff_ISR()
{
  digitalWrite(LED,LOW);
}

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(pinoLDRLow,INPUT);
  pinMode(pinoLDRHigh,INPUT);

  attachInterrupt(pinoLDRHigh, turnLEDOn_ISR, RISING);
  attachInterrupt(pinoLDRLow, turnLEDOff_ISR, FALLING);

  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  
  // Simula uma mudança de estado do LED
  delay(2000); // Espera 2 segundos
  digitalWrite(LED, !digitalRead(LED)); // Inverte o estado do LED

  // Verificar se houve uma mudança de estado do LED
  bool estadoAtual = digitalRead(LED);
  
  if (estadoAtual != estadoAnterior) {
    // Se o estado atual for diferente do estado anterior, imprimir na serial
    Serial.print("LED mudou de ");
    Serial.print(estadoAnterior ? "ligado para desligado" : "desligado para ligado");
    Serial.println();
    
    estadoAnterior = estadoAtual; // Atualizar o estado anterior
  }
}
