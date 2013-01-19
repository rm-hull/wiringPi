/*
 * bitBang.c:
 *	Software SPI.
 *	This is designed to drive the parallel interface LCD drivers
 *	based in the Hitachi HD44780U controller and compatables.
 *
 * Copyright (c) 2013 Richard Hull
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include "wiringPi.h"
#include "bitBang.h"

struct bitBangConfig
{
  // pins
  uint8_t csPin ;   // Chip Select
  uint8_t diPin ;   // Serial Data In
  uint8_t clkPin ;  // Clock

  // clock delay
  int pulseDelay ;
} ;

struct bitBangConfig *config [MAX_DEVICES] ;

int setupBitBang (uint8_t csPin, uint8_t diPin, uint8_t clkPin, int pulseDelay)
{
  static int initialized = 0 ;
  struct bitBangConfig *cfg ;
  int i;
  int cfgFd = -1;

  if (initialized == 0)
  {
    initialized = 1 ;
    for (i = 0 ; i < MAX_DEVICES ; ++i)
      config [i] = NULL;
  }

  for (i = 0 ; i < MAX_DEVICES ; ++i)
  {
    if (config [i] == NULL)
    {
      cfgFd = i ;
      break ;
    }
  }

  cfg = malloc (sizeof (struct bitBangConfig)) ;
  if (cfg == NULL)
  {
    if (wiringPiDebug) fprintf(stderr, "setupBitBang: cannot malloc %d bytes\n", sizeof(struct bitBangConfig));
    return -1;
  }

  cfg->csPin = csPin ;
  cfg->diPin = diPin ;
  cfg->clkPin = clkPin ;
  cfg->pulseDelay = pulseDelay ;

  config [cfgFd] = cfg ;

  return cfgFd ;
}

// transmit byte serially, MSB first
void digitalWriteSerial (int fd, uint8_t data)
{
  if (fd < 0 || fd > MAX_DEVICES || config [fd] == NULL)
  {
    if (wiringPiDebug) fprintf(stderr, "digitalWriteSerial: invalid fd specified (%d)\n", fd);
    return;
  }

  int i;
  struct bitBangConfig *cfg = config [fd];

  // select device
  digitalWrite (cfg->csPin, 0) ;    // Enable is low: TODO make this in config

  // send bits 7..0
  for (i = 0; i < 8; i++)
  {
    // consider leftmost bit
    // set line high if bit is 1, low if bit is 0
    if (data & 0x80)
      digitalWrite (cfg->diPin, 1) ;
    else
      digitalWrite (cfg->diPin, 0) ;

    // pulse clock to indicate that bit value should be read
    digitalWrite (cfg->clkPin, 1) ;
    delayMicroseconds (cfg->pulseDelay) ;
    digitalWrite (cfg->clkPin, 0) ;

    // shift byte left so next bit will be leftmost
    data <<= 1;
  }

  // deselect device
  digitalWrite (cfg->csPin, 1) ;
}
