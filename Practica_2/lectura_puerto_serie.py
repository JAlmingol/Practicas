# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.

https://www.luisllamas.es/controlar-arduino-con-python-y-la-libreria-pyserial/
"""
import serial
import time

i=1

#Serial takes two parameters: serial device and baudrate
arduino = serial.Serial('COM3', 9600)  #abrimos comunicación con el arduino
time.sleep(2)
while i <= 3:
    data = arduino.readline().strip()
   # data_decode = data.decode("base64")
    print(str(data))
    archivo_1 = open("datos_prueba_arduino.txt","a")  #ponemos a en lugar de w para añadir, no para escribr encima
    archivo_1.write(str(data))
    archivo_1.write(";\n")
    archivo_1.close()
arduino.close()  #cerramos comunicaciones con el arduino
