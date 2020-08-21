#!/bin/bash

# create a symbolic link between device file names and more convenient filenames
ln -s /dev/serial/by-id/ARDUINO_DEVICE /dev/sensorPort
ln -s /dev/serial/by-id/CELLULAR_MODULE /dev/cellularPort

# connect to internet via cellular module
pon cellularDevice 

# Needs to be put in loop, that restarts on transmitExecutable process exit
sleep 20 # simple delay works for now

#compile the executable, must be done on raspberry pi
#gcc -Wall -pedantic  -lwiring TransmitterCode.c -o transmitExecutable

# start the executale
./transmitExecutable
