//https://circuits4you.com/2018/12/31/esp32-pwm-example/
//pagina que explica el codigo del PWM para ESP32


//declaracion timer
volatile int interruptCounter;
hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

String option, option1;
int numRecib;
int Dutty = 150;
int salidaPWM;

const int freq = 5000;
const int resolution = 8;

int signalVoltios, ValorVoltios;
double ValorVoltiosAdc;
int pinPWM = 18;  // Poner pin correspondiente al PWM
int PWMchannel = 0;
const int puertoADC = 2;

int i1, i2, lectorADC, tiempoADC, contadorADC;
char e1 = '0';
char e2 = '0';

void IRAM_ATTR onTimer(){
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {

  //timer configuration
  timer = timerBegin (0, 80, true); //80MHz dividido entre 80, dejando 1MHZ de frecuencia y por tanto un timer de microsegundos
  timerAttachInterrupt(timer, &onTimer, true); //declara el timer de la interrupcion
  timerAlarmWrite(timer, 1000000, true); //indica momento alarma del timer, (vector de inicializacion, momento de alarma y true para reiniciar)
  timerAlarmEnable(timer);

  Serial.begin(9600);

  ledcSetup(PWMchannel, freq, resolution); //En principio así se ajusta frecuencia pwm y resolucion en bits, ponemos l amisma que la del conversor ADC para no necesitar un conversor a poseriori ya que la señal PWM depende del valor de este.
  ledcAttachPin(pinPWM, PWMchannel);

}

void loop() {
 
  
  salidaPWM = Dutty * 255;
  ledcWrite (PWMchannel, Dutty);

  if (interruptCounter > 0) {
    portENTER_CRITICAL_ISR(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL_ISR(&timerMux);

    contadorADC++;
    if (contadorADC > 9) {
      contadorADC = 0;
    }

    if (lectorADC == 1) {
      if (contadorADC == tiempoADC){
         ValorVoltios = analogRead(puertoADC);
  Serial.print(ValorVoltios);
  ValorVoltiosAdc = ValorVoltios * 0.000805;
        Serial.println("ValorVoltiosAdc = ");
      Serial.println(ValorVoltiosAdc);
      contadorADC = 0;
    }
  }
  }

  //comprobamos si se ha recibido un mensaje
  if (Serial.available() > 0) {
    //leemos
    option = Serial.readStringUntil('\n');
    Serial.println(option);


    if (option == "ADC") {
       ValorVoltios = analogRead(puertoADC);
  Serial.print(ValorVoltios);
  ValorVoltiosAdc = ValorVoltios * 0.000805;
      Serial.println("ValorVoltiosAdc = ");
      Serial.print(ValorVoltiosAdc);
    }
    if (option == "ADC(0)") {
      lectorADC = 0;
    }
    if (option == "ADC(1)") {
      lectorADC = 1;
      tiempoADC = 1;
    }
    if (option == "ADC(2)") {
      lectorADC = 1;
      tiempoADC = 2;
    }
    if (option == "ADC(3)") {
      lectorADC = 1;
      tiempoADC = 3;
    }
    if (option == "ADC(4)") {
      lectorADC = 1;
      tiempoADC = 4;
    }
    if (option == "ADC(5)") {
      lectorADC = 1;
      tiempoADC = 5;
    }
    if (option == "ADC(6)") {
      lectorADC = 1;
      tiempoADC = 6;
    }
    if (option == "ADC(7)") {
      lectorADC = 1;
      tiempoADC = 7;
    }
    if (option == "ADC(8)") {
      lectorADC = 1;
      tiempoADC = 8;
    }
    if (option == "ADC(9)") {
      lectorADC = 1;
      tiempoADC = 9;
    }

    if (option == "PWM(0)") {
      Dutty = 25;
    }
    if (option == "PWM(1)") {
      Dutty = 51;
    }
    if (option == "PWM(2)") {
      Dutty = 76;
    }
    if (option == "PWM(3)") {
      Dutty = 102;
    }
    if (option == "PWM(4)") {
      Dutty = 127;
    }
    if (option == "PWM(5)") {
      Dutty = 153;
    }
    if (option == "PWM(6)") {
      Dutty = 178;
    }
    if (option == "PWM(7)") {
      Dutty = 204;
    }
    if (option == "PWM(8)") {
      Dutty = 229;
    }
    if (option == "PWM(9)") {
      Dutty = 255;
    }

  }


}
