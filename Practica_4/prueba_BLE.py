# -*- coding: utf-8 -*-
"""
Created on Thu Dec 10 09:33:37 2020

@author: jorge
"""
from ruuvitag_sensor.ruuvitag import RuuviTag

#sensor = RuuviTag('AA:2C:6A:1E:59:3D')
sensor = RuuviTag('C4:4F:33:65:D2:4B')

# update state from the device
state = sensor.update()

# get latest state (does not get it from the device)
state = sensor.state

print(state)