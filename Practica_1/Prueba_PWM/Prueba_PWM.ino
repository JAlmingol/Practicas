//https://circuits4you.com/2018/12/31/esp32-pwm-example/
//pagina que explica el codigo del PWM para ESP32

const int freq = 5000;
const int resolution = 12;
int signalVoltios;
int lectorADC = 2;
int valorVoltiosAdc;
int pinPWM = 18;  // Poner pin correspondiente al PWM

void setup() {
  ledcSetup(pinPWM, freq, resolution); //En principio así se ajusta frecuencia pwm y resolucion en bits, ponemos l amisma que la del conversor ADC para no necesitar un conversor a poseriori ya que la señal PWM depende del valor de este.
   ledcAttachPin(lectorADC, pinPWM);
}

void loop() {
  valorVoltiosAdc = analogRead(lectorADC);  
   ledcWrite (pinPWM,2000);
   
  

}
