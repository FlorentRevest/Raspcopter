/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2013 - Florent Revest <florent.revest666@gmail.com>

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

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

typedef struct AccelGyroValues {
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;
} AccelGyroValues;

class Accelerometer 
{
public:
	Accelerometer();
	~Accelerometer();
	void setRegisterValue(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
	void getRegisterValue(uint8_t regAddr, uint8_t length, uint8_t *data);
	AccelGyroValues getAccelGyroValues();
	bool isConnected();

private:
	int m_i2cfd;
	bool m_isConnected;
};

#endif // _ACCELEROMETER_H_