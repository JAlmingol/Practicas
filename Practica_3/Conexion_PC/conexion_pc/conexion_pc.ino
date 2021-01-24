#include <Wire.h>
#include <WiFi.h>

const char* ssid = "RCasas";
const char* password = "";
const char* host ="127.0.0.1";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  //conecta a la red WiFi
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print(WiFi.status());
  }
  Serial.println("");
  Serial.println("Conectado con WiFi.");
  //Serial.println(WiFi.status());

 while(!client.connect(host, 21)) {
      Serial.print(".");
 }
      client.println("Conseguido");
      client.println();
 
}

void loop() {
}
