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

#include "Accelerometer.h"

Accelerometer::Accelerometer()
{
	m_isConnected = true;
    m_i2cfd = open("/dev/i2c-1", O_RDWR);
    if(!m_i2cfd < 0)
    	m_isConnected = false;
    if(ioctl(m_i2cfd, I2C_SLAVE, 0x68) < 0)
    	m_isConnected = false;

    setRegisterValue(0x6B, 2, 3, 1); // Choose the XGYRO clock
    setRegisterValue(0x1B, 4, 2, 1); // Set gyroscopes range to 500
    setRegisterValue(0x1C, 4, 2, 2); // Set accelerometer range to 8
    setRegisterValue(0x6B, 6, 1, 0); // Disable Sleep Mode
}

Accelerometer::~Accelerometer()
{
	close(m_i2cfd);
    setRegisterValue(0x6B, 6, 1, 1); // Disable Sleep Mode
}

AccelGyroValues Accelerometer::getAccelGyroValues()
{
	AccelGyroValues values;
    uint8_t buffer[14];
    getRegisterValue(0x3B, 14, buffer);

    values.ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    values.ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    values.az = (((int16_t)buffer[4]) << 8) | buffer[5];
    values.gx = (((int16_t)buffer[8]) << 8) | buffer[9];
    values.gy = (((int16_t)buffer[10]) << 8) | buffer[11];
    values.gz = (((int16_t)buffer[12]) << 8) | buffer[13];

    return values;
}

bool Accelerometer::isConnected()
{
	return m_isConnected;
}

// These two methods contain some code written by Jeff Rowberg for the I2Cdev" lib
void Accelerometer::setRegisterValue(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
	// Read the old value
    uint8_t value;
    getRegisterValue(regAddr, 1, &value);

    // Mix the new bits with the new ones
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1);
    data &= mask;
    value &= ~(mask);
    value |= data;

    // Write the new value to /dev/i2c-1
    uint8_t buffer[2] = {regAddr, value}; // The first octet is the register adress, the second contains the data
    write(m_i2cfd, buffer, 2);
}

void Accelerometer::getRegisterValue(uint8_t regAddr, uint8_t length, uint8_t *data)
{
    if(write(m_i2cfd, &regAddr, 1) != 1)
        return;
    int8_t count = read(m_i2cfd, data, length);
    if (count < 0 || count != 1)
        return;
}