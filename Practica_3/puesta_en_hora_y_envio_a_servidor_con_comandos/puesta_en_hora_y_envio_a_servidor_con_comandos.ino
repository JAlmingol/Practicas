#include <WiFi.h>
#include "time.h"
#include <SPI.h>


//declaracion timer
volatile int interruptCounter;
hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//datos red WiFi
char ssid[] = "MiFibra-8F9C";          //  your network SSID (name)
char pass[] = "645519569";   // your network password

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;   //si es gtm+1 3600, si es +2 7200 etc...
const int   daylightOffset_sec = 0; //3600;  //verano 3600, invierno 0.

String option, option1;

//constantes sistema control start/stop
int startCount = 0;


int status = WL_IDLE_STATUS;
IPAddress server(192, 168, 1, 14);
// Initialize the client library
WiFiClient client;


//Interrupcion temporizador
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}


void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    client.println("Failed to obtain time");
    return;
  }
  client.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(9600);

  //timer configuration
  timer = timerBegin (0, 80, true); //80MHz dividido entre 80, dejando 1MHZ de frecuencia y por tanto un timer de microsegundos
  timerAttachInterrupt(timer, &onTimer, true); //declara el timer de la interrupcion
  timerAlarmWrite(timer, 1000000, true); //indica momento alarma del timer, (vector de inicializacion, momento de alarma y true para reiniciar)
  timerAlarmEnable(timer);

  //connect to WiFi
  Serial.println("");
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, pass);
  Serial.println("esto esta estando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the real time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //connect to server
  Serial.println("conectando con el servidor local");
  // if you get a connection, report back via serial:
  if (client.connect(server, 98)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("conectado");
    client.println();

  }
}

void loop() {

  if (interruptCounter > 0) {
    portENTER_CRITICAL_ISR(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL_ISR(&timerMux);
    if (startCount == 1) {
      printLocalTime();
    }
  }

  if (client.available() > 0) {
    //leemos
    option = String(client.readStringUntil('\r'));
    client.println(option);
    Serial.println(option);
    Serial.println(startCount);
  }

  if (option == String("start")) {
    startCount = 1;
    Serial.println("entro al primer bucle");
  }
  if (option == String("stop")) {
    startCount = 0;
  }
}
