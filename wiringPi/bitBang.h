/*
 * bitBang.h:
 *  Probably replicates something better written elsewhere
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

#define	MAX_DEVICES	8

#ifdef __cplusplus
extern "C" {
#endif

extern int setupBitBang (uint8_t csPin, uint8_t diPin, uint8_t clkPin, int pulseDelay) ;

extern void digitalWriteSerial (int fd, uint8_t data) ;

#ifdef __cplusplus
}
#endif
