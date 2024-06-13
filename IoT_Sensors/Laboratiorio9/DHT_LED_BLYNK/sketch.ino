#define BLYNK_TEMPLATE_ID "TMPL2ApmKD1TE"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "c8PZCw4YEGqIYXxAQ0YrWFb6iTAwJSh9"
//#define THRESHOLD 30

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Defina suas credenciais de WiFi e token Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ELIAS ALEX OI_FIBRA 2.4";
char pass[] = "";

#define DHTPIN 15          // Pino onde o sensor DHT está conectado
#define DHTTYPE DHT22     // Tipo do sensor DHT (DHT11 ou DHT22)
#define LEDPIN 13          // Pino onde o LED está conectado
#define LDRPIN 23          // Pino onde o LDR está conectado


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
bool notificationSent = false;  // Flag para controle de notificação


void sendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int luminosity = analogRead(LDRPIN);  // Lê o valor do LDR
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }
  
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print("°C  Umidade: ");
  Serial.print(humidity);
  Serial.print("% Luminosidade: ");
  Serial.println(luminosity);

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, luminosity);  // Enviar luminosidade para o pino virtual V2

  if (temperature > 40 && !notificationSent) {
    //Blynk.notify("Alerta: Temperatura alta!");
    //Blynk.email("eliasalex10@gmail.com", "Alerta de Temperatura", "A temperatura excedeu 40°C.");
    Blynk.logEvent("temperatura_alta", String("Temperatura alta: ") + temperature + "°C");    
    notificationSent = true;  // Marca que a notificação foi enviada
  } else if (temperature <= 40) {
    notificationSent = false; // Reseta a flag quando a temperatura volta ao normal
  }

  if (luminosity < 500) {
    //Blynk.notify("Alerta: Luminosidade baixa!");
    //Blynk.email("eliasalex10@gmail.com", "Alerta de Luminosidade", "A luminosidade está abaixo de 500.");
    Blynk.logEvent("luminosidade_baixa", String("luminosidade Baixa: ") + luminosity + "°C");    
  }
}

// Função para controlar o LED
BLYNK_WRITE(V3) {
  int ledState = param.asInt();
  digitalWrite(LEDPIN, ledState);
  if (ledState == 1) 
    Serial.println("LED Ligado");
  else 
    Serial.println("LED Desligado");
}

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT); // Define o pino do LED como saída
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(5000L, sendSensorData); // Enviar dados a cada 5 segundos
}

void loop() {
  Blynk.run();
  timer.run(); // Executar BlynkTimer
}
