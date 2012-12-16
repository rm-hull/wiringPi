WiringPy
========
Python bindings for wiringPi. The following functions have been implemented:

    wiringPy.setup()

    wiringPy.board_revision()

    wiringPy.pin_mode(pin, mode)

    wiringPy.digital_write(pin, value)
    
    wiringPy.digital_write_byte(value)

    wiringPy.digital_read(pin)

    wiringPy.pwm_write(pin, value)

    wiringPy.pwm_set_mode(mode)

    wiringPy.pwm_set_range(range)

    wiringPy.pwm_set_clock(divisor)

    wiringPy.set_pad_drive(group, value)

    wiringPy.wait_for_interrupt(pin, ms)

    wiringPy.pull_up_down_control(pin, pud)

Building and installing
-----------------------
Ensure that the python headers are installed:

    sudo apt-get install python-dev

Assuming you've downloaded into ~/wiringPi:

    cd ~/wiringPi/wiringPi
    make clean all
    sudo make install

This will install all the (existing) wiringPi headers and libraries in
`/usr/local/include` and `/usr/local/lib`, but will also install the
self contained python bindings to `/usr/lib/python2.7/lib-dynload`.

Testing
-------
As per using the wiringPi libraries, you must have superuser privileges
so running any python program using wiringPy must either be prefixed with
`sudo` or somehow make /dev/mem available.

    sudo python ~/wiringPi/examples/test.py
