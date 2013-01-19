/*
 * wiringPy:
 * Python bindings for the Wiring library for the Raspberry Pi
 *    Copyright (c) 2012 Richard Hull
 ***********************************************************************
 * This file is part of wiringPi:
 *    https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with wiringPi.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <Python.h>
#include "wiringPi.h"
#include "bitBang.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static PyObject *WiringPyError;

static PyObject *wiringPy_debug(PyObject *self, PyObject *args) {
    const int flag;
    if (!PyArg_ParseTuple(args, "i", &flag)) return NULL;
    wiringPiDebug = flag;
    if (wiringPiDebug) fprintf(stderr, "debug(%d)\n", wiringPiDebug);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_setup(PyObject *self, PyObject *args) {
    int retval = wiringPiSetup();
    if (wiringPiDebug) fprintf(stderr, "wiringPiSetup() = %d\n", retval);
    return Py_BuildValue("i", retval);
}

static PyObject *wiringPy_setupSys(PyObject *self, PyObject *args) {
    int retval = wiringPiSetupSys();
    if (wiringPiDebug) fprintf(stderr, "wiringPiSetupSys() = %d\n", retval);
    return Py_BuildValue("i", retval);
}

static PyObject *wiringPy_setupGpio(PyObject *self, PyObject *args) {
    int retval = wiringPiSetupGpio();
    if (wiringPiDebug) fprintf(stderr, "wiringPiSetupGpio() = %d\n", retval);
    return Py_BuildValue("i", retval);
}

static PyObject *wiringPy_setupBitBang(PyObject *self, PyObject *args) {
    const int csPin, diPin, clkPin, pulseDelay;
    if (!PyArg_ParseTuple(args, "iiii", &csPin, &diPin, &clkPin, &pulseDelay)) return NULL;
    int retval = setupBitBang(csPin, diPin, clkPin, pulseDelay);
    if (wiringPiDebug) fprintf(stderr, "setupBitBang(%d, %d, %d, %d) = %d\n", csPin, diPin, clkPin, pulseDelay, retval);
    return Py_BuildValue("i", retval);
}

static PyObject *wiringPy_boardRevision(PyObject *self, PyObject *args) {
    int retval = piBoardRev();
    if (wiringPiDebug) fprintf(stderr, "piBoardRev() = %d\n", retval);
    return Py_BuildValue("i", retval);
}

static PyObject *wiringPy_pinMode(PyObject *self, PyObject *args) {
    const int pin, mode;
    if (!PyArg_ParseTuple(args, "ii", &pin, &mode)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pinMode(%d, %d)\n", pin, mode);
    pinMode(pin, mode);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_digitalWrite(PyObject *self, PyObject *args) {
    const int pin, value;
    if (!PyArg_ParseTuple(args, "ii", &pin, &value)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "digitalWrite(%d, %d)\n", pin, value);
    digitalWrite(pin, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_digitalWriteByte(PyObject *self, PyObject *args) {
    const int value;
    if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "digitalWriteByte(%d)\n", value);
    digitalWriteByte(value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_digitalWriteSerial(PyObject *self, PyObject *args) {
    const int device, data;
    if (!PyArg_ParseTuple(args, "ii", &device, &data)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "digitalWriteSerial(%d,%d)\n", device, data);
    digitalWriteSerial(device, data);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_digitalRead(PyObject *self, PyObject *args) {
    const int pin;
    if (!PyArg_ParseTuple(args, "i", &pin)) return NULL;
    int value = digitalRead(pin);
    if (wiringPiDebug) fprintf(stderr, "digitalRead(%d) = %d\n", pin, value);
    return Py_BuildValue("i", value);
}

static PyObject *wiringPy_pwmWrite(PyObject *self, PyObject *args) {
    const int pin, value;
    if (!PyArg_ParseTuple(args, "ii", &pin, &value)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pwmWrite(%d, %d)\n", pin, value);
    pwmWrite(pin, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_pwmSetMode(PyObject *self, PyObject *args) {
    const int mode;
    if (!PyArg_ParseTuple(args, "i", &mode)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pwmSetMode(%d)\n", mode);
    pwmSetMode(mode);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_pwmSetRange(PyObject *self, PyObject *args) {
    const unsigned int range;
    if (!PyArg_ParseTuple(args, "I", &range)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pwmSetRange(%d)\n", range);
    pwmSetRange(range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_pwmSetClock(PyObject *self, PyObject *args) {
    const int divisor;
    if (!PyArg_ParseTuple(args, "i", &divisor)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pwmSetClock(%d)\n", divisor);
    pwmSetClock(divisor);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_setPadDrive(PyObject *self, PyObject *args) {
    const int group, value;
    if (!PyArg_ParseTuple(args, "ii", &group, &value)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "setPadDrive(%d, %d)\n", group, value);
    setPadDrive(group, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *wiringPy_waitForInterrupt(PyObject *self, PyObject *args) {
    const int pin, ms;
    if (!PyArg_ParseTuple(args, "ii", &pin, &ms)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "waitForInterrupt(%d, %d)\n", pin, ms);
    int value = waitForInterrupt(pin, ms);
    return Py_BuildValue("i", value);
}

static PyObject *wiringPy_pullUpDownControl(PyObject *self, PyObject *args) {
    const int pin, pud;
    if (!PyArg_ParseTuple(args, "ii", &pin, &pud)) return NULL;
    if (wiringPiDebug) fprintf(stderr, "pullUpDnControl(%d, %d)\n", pin, pud);
    pullUpDnControl(pin, pud);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef WiringPyMethods[ ] = {
    { "debug",                (PyCFunction)wiringPy_debug,              METH_VARARGS, "Sets debug log tracing on/off." },
    { "setup",                (PyCFunction)wiringPy_setup,              METH_NOARGS,  "Must be called once at the start of your program execution." },
    { "setup_sys",            (PyCFunction)wiringPy_setupSys,           METH_NOARGS,  "Must be called once at the start of your program execution." },
    { "setup_gpio",           (PyCFunction)wiringPy_setupGpio,          METH_NOARGS,  "Must be called once at the start of your program execution." },
    { "setup_bitbang",        (PyCFunction)wiringPy_setupBitBang,       METH_VARARGS, "Must be called once at the start of your program execution if using digital_write_serial." },
    { "board_revision",       (PyCFunction)wiringPy_boardRevision,      METH_NOARGS,  "Return a number representing the hardware revision of the board. Revision is currently 1 or 2. -1 is returned on error." },
    { "pin_mode",             (PyCFunction)wiringPy_pinMode,            METH_VARARGS, "Sets the mode of a pin to be input, output or PWM output." },
    { "digital_write",        (PyCFunction)wiringPy_digitalWrite,       METH_VARARGS, "Set an output bit." },
    { "digital_write_byte",   (PyCFunction)wiringPy_digitalWriteByte,   METH_VARARGS, "Write an 8-bit byte to the first 8 GPIO pins." },
    { "digital_write_serial", (PyCFunction)wiringPy_digitalWriteSerial, METH_VARARGS, "Bit-bangs the byte according to the CS/DI/CLK pins of the configured SPI device." },
    { "digital_read",         (PyCFunction)wiringPy_digitalRead,        METH_VARARGS, "Read the value of a given Pin, returning HIGH or LOW." },
    { "pwm_write",            (PyCFunction)wiringPy_pwmWrite,           METH_VARARGS, "Set an output PWM value." },
    { "pwm_set_mode",         (PyCFunction)wiringPy_pwmSetMode,         METH_VARARGS, "Allow the user to control some of the PWM functions." },
    { "pwm_set_range",        (PyCFunction)wiringPy_pwmSetRange,        METH_VARARGS, "." },
    { "pwm_set_clock",        (PyCFunction)wiringPy_pwmSetClock,        METH_VARARGS, "Set/Change the PWM clock." },
    { "set_pad_drive",        (PyCFunction)wiringPy_setPadDrive,        METH_VARARGS, "Set the PAD driver value." },
    { "wait_for_interrupt",   (PyCFunction)wiringPy_waitForInterrupt,   METH_VARARGS, "Wait for Interrupt on a GPIO pin." },
    { "pull_up_down_control", (PyCFunction)wiringPy_pullUpDownControl,  METH_VARARGS, "Control the internal pull-up/down resistors on a GPIO pin." },
    { NULL, NULL, 0, NULL }     /* Sentinel */
};

PyMODINIT_FUNC initwiringPy (void) {
    PyObject *m;

    m = Py_InitModule("wiringPy", WiringPyMethods);
    if (m == NULL)
        return;

    WiringPyError = PyErr_NewException("wiringPy.error", NULL, NULL);
    Py_INCREF(WiringPyError);
    PyModule_AddObject(m, "error", WiringPyError);

    return;
}

