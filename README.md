WiringPy
========
Python bindings for wiringPi. The following functions have been implemented:

    wiringPy.debug(value);

    wiringPy.setup()
    
    wiringPy.setup_gpio()

    wiringPy.setup_spi()

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

TODO
----
* Implement a C routine and Python bindings for 
  [bit-banging](https://en.wikipedia.org/wiki/Bit-banging)
  along the lines of the following, but supply a stream of 
  bytes to be processed in one go. CS/DI/CLK pin-id's to be
  supplied in parameters.

    // transmit byte serially, MSB first
    void send_8bit_serial_data(unsigned char data)
    {
       int i;
     
       // select device
       output_high(SD_CS);
     
       // send bits 7..0
       for (i = 0; i < 8; i++)
       {
           // consider leftmost bit
           // set line high if bit is 1, low if bit is 0
           if (data & 0x80)
               output_high(SD_DI);
           else
               output_low(SD_DI);
     
           // pulse clock to indicate that bit value should be read
           output_low(SD_CLK);
           output_high(SD_CLK);
     
           // shift byte left so next bit will be leftmost
           data <<= 1;
       }
     
       // deselect device
       output_low(SD_CS);
    }

