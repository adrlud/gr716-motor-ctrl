#!cmd
# GAISLER_LICENSE
# ---------------------------------------------------------------------------
# File:        agilent_dmm.py
# Author:      Lucas Antunes Tambara - Cobham Gaisler
# Description: Script to control the Keysight Agilent 34401A multimeter 
# ---------------------------------------------------------------------------

#############################################################################
# TODO
#   - in its current state, the script converts voltage measurements from a 
#     thermocouple type K to temperature values
#   - this script was made in a hurry, so there a lot of room for improvements
#############################################################################

import sys
import time
from datetime import datetime
import logging
import serial
from serial import SerialException
import random

class SCPI:
    def __init__(self, device, port):
        self.device = device
        self.port = port
        try:
            if self.port == 'file':
                f = open(self.device, 'w')
            if self.port == 'serial':
               f = serial.Serial(port=self.device, baudrate=38400, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_TWO, timeout=1, rtscts=False, write_timeout=10, dsrdtr=True)
               logger.info("\nPython connected to: '%s'" % f)
            f.close()
            self.debug = False
        except SerialException:
            self.debug = True
            logger.info("\nPython not connected to: '%s'" % self.device)

    def scpi_comm(self,command):
        if self.debug:
            return str(random.random())
        if self.port == 'file':
            f = open(self.device, 'w')
        if self.port == 'serial':
            f = serial.Serial(port=self.device, baudrate=38400, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_TWO, timeout=1, rtscts=False, write_timeout=10, dsrdtr=True)
            command = command + '\n'
        f.write(str(command).encode())
        time.sleep(0.5)
        return_string = ""
        if '?' in command:
            return_string = f.readline()
        f.close()
        return return_string

    def readSoftwareVersion(self):
        version_string = self.scpi_comm("*IDN?")
        return(version_string)
        
    def resetDevice(self):
        self.scpi_comm("*RST")
        return(True)
    
    def deviceClear(self):
        self.scpi_comm("*CLS")
        return(True)





def setup_custom_logger(name):
    formatter = logging.Formatter(fmt='%(asctime)s %(levelname)-8s %(message)s', datefmt='%Y-%m-%d %H:%M:%S')
    handler = logging.FileHandler(''.join([name, '.log']), mode='w')
    handler.setFormatter(formatter)
    screen_handler = logging.StreamHandler(stream=sys.stdout)
    screen_handler.setFormatter(formatter)
    logger = logging.getLogger(name)
    logger.setLevel(logging.DEBUG)
    logger.addHandler(handler)
    logger.addHandler(screen_handler)
    return logger

#############################################################################
# main
#############################################################################

# generate a filename based on the current date and time



dt = datetime.now()
file_name = dt.strftime("%Y%m%d_%H%M%S")

logger = setup_custom_logger(file_name)

file_csv = open(''.join([file_name, '.csv']), 'w')


hej = SCPI('/dev/ttyUSB2', 'serial')
while True:
    read_data = hej.scpi_comm('?')
    print(read_data)
