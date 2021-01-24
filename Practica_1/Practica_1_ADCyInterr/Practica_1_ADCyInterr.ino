
//declaracion timer
volatile int interruptCounter;
hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;




const int pin3v3 = 3.3;
const int lectorADC = 2; 
float valorVoltiosAdc;
float valor_voltios = 0;
int contador = 0;


void IRAM_ATTR onTimer(){
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(9600);

  //timer configuration
  timer = timerBegin (0, 80, true); //80MHz dividido entre 80, dejando 1MHZ de frecuencia y por tanto un timer de microsegundos
  timerAttachInterrupt(timer, &onTimer, true); //declara el timer de la interrupcion
  timerAlarmWrite(timer, 10000000, true); //indica momento alarma del timer, (vector de inicializacion, momento de alarma y true para reiniciar)
  timerAlarmEnable(timer);

  
  pinMode (pin3v3, OUTPUT);
  
}

void loop() {

  if(interruptCounter > 0){
    portENTER_CRITICAL_ISR(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL_ISR(&timerMux);

  
  

  
  contador=contador+1;
  valorVoltiosAdc = analogRead(lectorADC);//*(5/4095);
  valor_voltios = valorVoltiosAdc * 0.000805;
  Serial.print("Medida del sensor numero ");
  Serial.println(contador);
  Serial.print("sensor value en 0-4096 = ");
  Serial.println(valorVoltiosAdc);
  Serial.print("sensor value en Voltios = ");
  Serial.println(valor_voltios);
  Serial.println("");
  Serial.println("");
 
  //delay (5000);

  }
  

}
