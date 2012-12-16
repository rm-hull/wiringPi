#!/usr/bin/env python

import time
import wiringPy

if wiringPy.setup() < 0:
    print "Failed to initialize wiringPi"
    exit(-1)

print "Rasberry Pi - Board revision:" , wiringPy.board_revision()

wiringPy.pin_mode(1, 2)

for bright in range(0, 1024):
    wiringPy.pwm_write(1, bright)
    time.sleep(0.001)

for bright in range(1024, -1, -1):
    wiringPy.pwm_write(1, bright)
    time.sleep(0.001)

for pin in range(0, 8):
    wiringPy.pin_mode(pin, 1)

for i in range(0, 256):
    wiringPy.digital_write_byte(i)
    time.sleep(0.02)

wiringPy.digital_write_byte(0)

