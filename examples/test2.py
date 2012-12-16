#!/usr/bin/env python

import time
import wiringPy

if wiringPy.setup_sys() < 0:
    print "Failed to initialize wiringPi"
    exit(-1)

print "Rasberry Pi - Board revision:" , wiringPy.board_revision()

for i in range(0, 32):
    wiringPy.digital_write(i, 1)
    time.sleep(0.2)

for i in range(0,32):
    wiringPy.digital_write(i, 0)
    time.sleep(0.2)
