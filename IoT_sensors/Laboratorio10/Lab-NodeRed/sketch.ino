#include <WiFi.h>
#include <PubSubClient.h>

// Configurações WiFi
const char* ssid = "WP3-CETELI-2-IA";           // Substitua pelo seu SSID
const char* password = "RioNhamunda";      // Substitua pela sua senha

// Configurações MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_topic_reservatorio = "22052989/reservatorio";
const char* mqtt_topic_nivelReservatorio = "22052989/nivelReservatorio";

WiFiClient espClient;
PubSubClient client(espClient);

const int potPin = 36;  // Pin do potenciômetro
const int ledVermelho = 26;
const int ledVerde = 27;
const int ledAzul = 25;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  Serial.print("Mensagem recebida: " + incoming);
  int nivel = incoming.toInt();
  Serial.print("Nivel recebido: ");
  Serial.println(nivel);
  if (nivel == 1) {
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAzul, LOW);
  } else if (nivel == 2) {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAzul, LOW);
  } else if (nivel == 3) {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAzul, HIGH);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado");
      client.subscribe(mqtt_topic_nivelReservatorio);
      Serial.print("Inscrito no tópico: ");
      Serial.println(mqtt_topic_nivelReservatorio);
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensorValue = analogRead(potPin);
  float levelPercent = sensorValue / 4095.0 * 100;
  char msg[50];
  snprintf(msg, 50, "%d", sensorValue);
  Serial.print("Publicando: ");
  Serial.println(msg);
  client.publish(mqtt_topic_reservatorio, msg);
  
  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}