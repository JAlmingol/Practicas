# -*- coding: utf-8 -*-
"""
Created on Tue Nov  3 20:31:09 2020

@author: jorge
"""


import serial
import time
import matplotlib.pyplot as plt
import csv
import base64
import json
import numpy as np
import statistics


Conectado = True
i=1
a=0
r=0
contador1, contador2 = 0, 5
datos = np.zeros(50)


plt.figure()
plot1 = plt.subplot(2,2,1)
plot2 = plt.subplot(2,2,2)
plot3 = plt.subplot(2,2,3)



try:
    #Serial takes two parameters: serial device and baudrate
    arduino = serial.Serial('COM3', 9600)  #abrimos comunicación con el arduino
except serial.SerialException:
    print("No Conectado")
    Conectado = False
    
    

    
while Conectado:
    try:
       # time.sleep(2)
        try:
            data = arduino.readline().decode("ascii")
        except UnicodeDecodeError:
            print("")
      #data = data.decode("ascii")       
      # data_decode = data.decode("base64")
        if a == 1:
            data = data.replace("\n","") 
            data = data.replace("\r","") 
            data = data.replace("\\","") 
            data = data.rstrip('\n') 
            temp = data.split(',') 
        
                
            datos[i] = int(data)/2000
            i=i+1

            
            
            print(data)
            plot1.plot(contador1 / 10 , int(data)/2000 , 'o', c='r')
            
        
            archivo_1 = open("datos_prueba_arduino.txt","a")  #ponemos a en lugar de w para añadir, no para escribr encima
            archivo_1.write(data)
            archivo_1.write(";\n")
            archivo_1.close()
        
            contador1=contador1+1
        a=1  
        
    except serial.SerialException:
        print("no se puede leer")
        arduino.close()  #cerramos comunicaciones con el arduino
    
    if i == 50:
        i=0
        
        media = datos.mean()  
        print ("esta es la media =")
        print (media)
        plot2.plot(contador2, media, '^-', c='y')
        
        varianza = datos.var()
        plot3.plot(contador2, varianza, 'o-', c='g')
        
        desviacionTipica = datos.std()
       #plot3.plot(contador2, desviacionTipica, marker = 'x', c='b')
        
        contador2=contador2+5
        plt.show()
    
    
    
    
    
    
    
    
    
    
    
    