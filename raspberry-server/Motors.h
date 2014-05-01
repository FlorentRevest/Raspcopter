/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2014 - Florent Revest <florent.revest666@gmail.com>

 * Raspcopter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Raspcopter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Raspcopter.  If not, see <http://www.gnu.org/licenses/>.
 * ================================================================== */

#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>

#include <libusb.h>

// These are the channels I chose on my Pololu Maestro for every ESC
#define MOTOR_FL 5
#define MOTOR_FR 3
#define MOTOR_BL 4
#define MOTOR_BR 2

class Motors
{
public:
    Motors();
    ~Motors();
    unsigned short getSpeed(unsigned char channel);
    void setSpeed(unsigned char channel, unsigned short target);
    void setToZero();

private:
    libusb_context *ctx;
    libusb_device_handle *device_handle;
    unsigned short speeds[6];
};

#endif // _MOTORS_H

