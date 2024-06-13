#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações do DHT22
#define DHTPIN 23     // Pino conectado ao DHT22
#define DHTTYPE DHT22

// Configuração WiFi
const char* ssid = "Wokwi-GUEST";
//const char* password = "123456";

// Configuração MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* topicIn = "In21952406"; // Tópico de entrada com sua matrícula
const char* topicTemp = "Out21952406/Temperatura";
const char* topicHum = "Out21952406/Umidade";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos dos LEDs
const int ledPin1 = 5;
const int ledPin2 = 18;
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsg = 0; // Variável para controlar o tempo das publicações

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (message == "1L") {
    digitalWrite(ledPin1, HIGH);
  } else if (message == "1D") {
    digitalWrite(ledPin1, LOW);
  } else if (message == "2L") {
    digitalWrite(ledPin2, HIGH);
  } else if (message == "2D") {
    digitalWrite(ledPin2, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(topicIn);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  dht.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    // Ler os valores de temperatura e umidade do DHT22
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Verifica se leitura falhou e sai cedo (para tentar novamente).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Publicar temperatura e umidade
    char tempMsg[50];
    sprintf(tempMsg, "Umidade: %f %%, Temperatura: %f C", humidity, temperature);
    Serial.println(tempMsg);
    client.publish(topicTemp, String(temperature).c_str());
    client.publish(topicHum, String(humidity).c_str());
  }
}