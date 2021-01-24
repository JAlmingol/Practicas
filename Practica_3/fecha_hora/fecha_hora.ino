#include <WiFi.h>
#include "time.h"

const char* ssid       = "Jorge_Almin";
const char* password   = "iotdejorge";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;   //si es gtm+1 3600, si es +2 7200 etc...
const int   daylightOffset_sec = 0; //3600;  //verano 3600, invierno 0.

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(9600);
  
  //connect to WiFi
  Serial.println("");
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  Serial.println("esto esta estando");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
