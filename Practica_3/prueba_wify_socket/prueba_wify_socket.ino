#include <SPI.h>
#include <WiFi.h>

char ssid[] = "MiFibra-8F9C";          //  your network SSID (name)
char pass[] = "645519569";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(192,168,1,14); 

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print(WiFi.status());
  }
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 21)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("funcionaaa");
      client.println();
    }
  }


void loop() {
//  if (!client.connect(server, 21)) {
//      Serial.println("error de conexion");
//      return;
//  }
//      // Make a HTTP request:
//      client.println("Conseguido");
//      client.println();
  





  
}
