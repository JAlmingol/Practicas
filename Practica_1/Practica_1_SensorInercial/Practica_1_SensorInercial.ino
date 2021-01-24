#include <Wire.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18



//declaracion timer
volatile int interruptCounter;
hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


const int pin3v3 = 3.3;
const int lectorADC = 2;
const int LEDpin = 5;


float valorVoltiosAdc;
float valor_voltios = 0;
int contador = 0;
int contadorEnvio;
int LED = 0;
int datos[10];


void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}


//Funcion auxiliar lectura
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}


// Funcion auxiliar de escritura
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);


  //timer configuration
  timer = timerBegin (0, 80, true); //80MHz dividido entre 80, dejando 1MHZ de frecuencia y por tanto un timer de microsegundos
  timerAttachInterrupt(timer, &onTimer, true); //declara el timer de la interrupcion
  timerAlarmWrite(timer, 100000, true); //indica momento alarma del timer, (vector de inicializacion, momento de alarma y true para reiniciar)
  timerAlarmEnable(timer);



  // Configurar acelerometro
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);

  // Configurar giroscopio
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);


  pinMode (pin3v3, OUTPUT);
  pinMode (LEDpin, OUTPUT);

}

void loop() {


  if (interruptCounter > 0) {
    portENTER_CRITICAL_ISR(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL_ISR(&timerMux);

    contadorEnvio++;
    LED++;

    // ---  Lectura acelerometro y giroscopio ---
    uint8_t Buf[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

    // Convertir registros acelerometro
    int16_t ax = -(Buf[0] << 8 | Buf[1]);
    int16_t ay = -(Buf[2] << 8 | Buf[3]);
    int16_t az = Buf[4] << 8 | Buf[5];

    // Convertir registros giroscopio
    int16_t gx = -(Buf[8] << 8 | Buf[9]);
    int16_t gy = -(Buf[10] << 8 | Buf[11]);
    int16_t gz = Buf[12] << 8 | Buf[13];


    //Serial.println(ax, DEC);
    datos[contadorEnvio-1] = ax ;

  }

  if (contadorEnvio == 10) {
    LED = 0;
    contador = contador + 1;
    //Serial.print("Medida del sensor numero ");
    //Serial.println(contador);
    //Serial.println("sensor value = ");
    Serial.println(datos[0], DEC);
    Serial.println(datos[1], DEC);
    Serial.println(datos[2], DEC);
    Serial.println(datos[3], DEC);
    Serial.println(datos[4], DEC);
    Serial.println(datos[5], DEC);
    Serial.println(datos[6], DEC);
    Serial.println(datos[7], DEC);
    Serial.println(datos[8], DEC);
    Serial.println(datos[9], DEC);
//    Serial.println("");
//    Serial.println("");
    contadorEnvio = 0;
  }

  if (LED < 2) {
    digitalWrite (LEDpin, LOW);

  } else {
    digitalWrite (LEDpin, HIGH);
  }


}
