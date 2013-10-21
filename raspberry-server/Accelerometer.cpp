/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2013 - Florent Revest <florent.revest666@gmail.com>
 *
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

/* 
 * /!\ Huge thanks to Noah Zerkin and Jeff Rowberg, without their amazing work the MPU6050 couldn't be used !
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>
#include "Accelerometer.h"

Accelerometer::Accelerometer()
{
    m_isConnected = true;

    m_i2cfd = open("/dev/i2c-1", O_RDWR);
    if(!m_i2cfd < 0)
    	m_isConnected = false;
    if(ioctl(m_i2cfd, I2C_SLAVE, 0x68) < 0)
    	m_isConnected = false;

    i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO); // Set Clock source
    i2cWriteBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250); // Full scale gyro range
    i2cWriteBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU6050_ACCEL_FS_2); // Full scale accel range
    i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 1, false); // Disable sleep mode

    i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, 1, true); // Reset
    usleep(30000); 
    i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 1, false); // Disable sleep mode
    setMemoryBank(0x10, true, true); // Get MPU hardware revision
    uint8_t value = 0x06; // Alright, this is dirty but a pointer to this value will be sent to every i2cWriteBytes...
    uint16_t value16; // Yeah... I know, I won't go to heaven but that's ok
    i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &value); // Set memory start address
    i2cReadBytes(MPU6050_RA_MEM_R_W, 1, buffer); // Get hardware revision
    uint8_t hwRevision __attribute__((__unused__)) = buffer[0];
    setMemoryBank(0, false, false);

    i2cReadBits(MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OTP_BNK_VLD_BIT, 1, buffer);
    uint8_t otpValid __attribute__((__unused__)) = buffer[0]; // Check OTP bank validity

    i2cReadBits(MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
    int8_t xgOffset = buffer[0];
    i2cReadBits(MPU6050_RA_YG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
    int8_t ygOffset = buffer[0];
    i2cReadBits(MPU6050_RA_ZG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
    int8_t zgOffset = buffer[0];

    value = 0x7F; // Setup weird slave stuff
    i2cWriteBytes(MPU6050_RA_I2C_SLV0_ADDR, 1, &value);
    i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, 1, false); // Disable I2C Master Mode
    value = 0x68;
    i2cWriteBytes(MPU6050_RA_I2C_SLV0_ADDR, 1, &value);
    i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_RESET_BIT, 1, true); // Reset I2C Master
    usleep(20000);
    
    if (writeMemoryBlock(dmpMemory, MPU6050_DMP_CODE_SIZE, 0, 0, true, true)) // Load DMP code into memory banks
    {
        if (writeDMPConfigurationSet(dmpConfig, MPU6050_DMP_CONFIG_SIZE, true)) // Let's write the DMP configuration
        {
            i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_ZGYRO); // Set clock source
            value = 0x12;
            i2cWriteBytes(MPU6050_RA_INT_ENABLE, 1, &value); // Enable 0x12 interuption
            value = 4; // 1khz / (1 + 4) = 200 Hz
            i2cWriteBytes(MPU6050_RA_SMPLRT_DIV, 1, &value);
            i2cWriteBits(MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, MPU6050_EXT_SYNC_TEMP_OUT_L); // External Frame Sync
            i2cWriteBits(MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, MPU6050_DLPF_BW_42); // DLPF Mode
            i2cWriteBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_2000); // Full scale gyro range
            value = 0x03;
            i2cWriteBytes(MPU6050_RA_DMP_CFG_1, 1, &value);
            value = 0x00;
            i2cWriteBytes(MPU6050_RA_DMP_CFG_2, 1, &value);

            // Setting X Y and Z gyro offsets to previous values
            i2cWriteBits(MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, xgOffset);
            i2cWriteBits(MPU6050_RA_YG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, ygOffset);
            i2cWriteBits(MPU6050_RA_ZG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, zgOffset);

            value16 = 0; // And gyro offsets users to 0
            i2cWriteWords(MPU6050_RA_XG_OFFS_USRH, 1, &value16);
            i2cWriteWords(MPU6050_RA_YG_OFFS_USRH, 1, &value16);
            i2cWriteWords(MPU6050_RA_ZG_OFFS_USRH, 1, &value16);

            // Memory update 1/7
            uint8_t dmpUpdate[16], j;
            uint16_t pos = 0;
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);

            //Memory update 2/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);
            resetFIFO();
            uint8_t fifoCount = getFIFOCount();
            uint8_t fifoBuffer[128];
            value = 2;
            i2cWriteBytes(MPU6050_RA_MOT_THR, 1, &value); // Motion threshold
            value = 156;
            i2cWriteBytes(MPU6050_RA_ZRMOT_THR, 1, &value); // Zero Motion threshold
            value = 80;
            i2cWriteBytes(MPU6050_RA_MOT_DUR, 1, &value); // Motion duration
            value = 0;
            i2cWriteBytes(MPU6050_RA_ZRMOT_DUR, 1, &value); // Zero Motion duration
            resetFIFO();
            setFIFOEnabled(true);
            setDMPEnabled(true);
            i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_RESET_BIT, 1, true); // Reset DMP

            // Memory update 3/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);

            // Memory update 4/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);

            // Memory update 5/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);
            while ((fifoCount = getFIFOCount()) < 3);
            getFIFOBytes(fifoBuffer, fifoCount);
            uint8_t mpuIntStatus __attribute__((__unused__)) = getIntStatus();

            // Memory update 6/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            readMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);
            while ((fifoCount = getFIFOCount()) < 3);
            getFIFOBytes(fifoBuffer, fifoCount);
            mpuIntStatus = getIntStatus();

            // Memory update 7/7
            for (j = 0; j < 4 || j < dmpUpdate[2] + 3; j++, pos++)
                dmpUpdate[j] = pgm_read_byte(&dmpUpdates[pos]);
            writeMemoryBlock(dmpUpdate + 3, dmpUpdate[2], dmpUpdate[0], dmpUpdate[1]);

            setDMPEnabled(false);
            dmpPacketSize = 42;
            resetFIFO();
            getIntStatus();
        }
        else
            m_isConnected = false;
    }
    else
        m_isConnected = false;

    if(m_isConnected)
    {
        i2cReadBits(MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, buffer);
        m_isConnected = buffer[0] == 0x34;
    }
}

Accelerometer::~Accelerometer()
{
	close(m_i2cfd);
    i2cWriteBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 1, true); // Enable sleep mode
}

bool Accelerometer::isConnected()
{
	return m_isConnected;
}

uint8_t Accelerometer::getQuaternion(int16_t *data, const uint8_t* packet)
{
    if (packet == 0)
        packet = dmpPacketBuffer;
    data[0] = ((packet[0] << 8) + packet[1]);
    data[1] = ((packet[4] << 8) + packet[5]);
    data[2] = ((packet[8] << 8) + packet[9]);
    data[3] = ((packet[12] << 8) + packet[13]);
    return 0;
}

uint8_t Accelerometer::getQuaternion(Quaternion *q, const uint8_t* packet)
{
    int16_t qI[4];
    uint8_t status = getQuaternion(qI, packet);
    if (status == 0)
    {
        q -> w = (float)qI[0] / 16384.0f;
        q -> x = (float)qI[1] / 16384.0f;
        q -> y = (float)qI[2] / 16384.0f;
        q -> z = (float)qI[3] / 16384.0f;
        return 0;
    }
    return status; 
}

uint8_t Accelerometer::getGravity(VectorFloat *v, Quaternion *q)
{
    v -> x = 2 * (q -> x*q -> z - q -> w*q -> y);
    v -> y = 2 * (q -> w*q -> x + q -> y*q -> z);
    v -> z = q -> w*q -> w - q -> x*q -> x - q -> y*q -> y+q -> z*q -> z;
    return 0;
}

uint8_t Accelerometer::getYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity)
{
    data[0] = atan2(2*q -> x*q -> y - 2*q -> w*q -> z, 2*q -> w*q -> w + 2*q -> x*q -> x - 1);
    data[1] = atan(gravity -> x / sqrt(gravity -> y*gravity -> y + gravity -> z*gravity -> z));
    data[2] = atan(gravity -> y / sqrt(gravity -> x*gravity -> x + gravity -> z*gravity -> z));
    return 0;
}

uint16_t Accelerometer::getFIFOPacketSize()
{
    return dmpPacketSize;
}

uint8_t Accelerometer::getIntStatus()
{
    i2cReadBytes(MPU6050_RA_INT_STATUS, 1, buffer);
    return buffer[0];
}

void Accelerometer::setFIFOEnabled(bool enabled)
{
    i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_EN_BIT, 1, enabled);
}

void Accelerometer::resetFIFO()
{
    i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, 1, true);
}

uint16_t Accelerometer::getFIFOCount()
{
    i2cReadBytes(MPU6050_RA_FIFO_COUNTH, 2, buffer);
    return (((uint16_t)buffer[0]) << 8) | buffer[1];
}

void Accelerometer::getFIFOBytes(uint8_t *data, uint8_t length)
{
    i2cReadBytes(MPU6050_RA_FIFO_R_W, length, data);
}

void Accelerometer::setDMPEnabled(bool enabled)
{
    i2cWriteBits(MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_EN_BIT, 1, enabled);
}

void Accelerometer::setMemoryBank(uint8_t bank, bool prefetchEnabled, bool userBank)
{
    bank &= 0x1F;
    if (userBank)
        bank |= 0x20;
    if (prefetchEnabled)
        bank |= 0x40;
    i2cWriteBytes(MPU6050_RA_BANK_SEL, 1, &bank);
}

void Accelerometer::readMemoryBlock(uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address) {
    setMemoryBank(bank);
    i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &address); // Set memory start address
    uint8_t chunkSize;
    for (uint16_t i = 0; i < dataSize;)
    {
        chunkSize = MPU6050_DMP_MEMORY_CHUNK_SIZE;
        if (i + chunkSize > dataSize)
            chunkSize = dataSize - i;
        if (chunkSize > 256 - address)
            chunkSize = 256 - address;

        i2cReadBytes(MPU6050_RA_MEM_R_W, chunkSize, data + i);
        
        i += chunkSize;
        address += chunkSize;

        if (i < dataSize)
        {
            if (address == 0)
                bank++;
            setMemoryBank(bank);
            i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &address); // Set Memory start address
        }
    }
}
bool Accelerometer::writeMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, bool verify, bool useProgMem)
{
    setMemoryBank(bank);
    i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &address); // Set Memory start address
    uint8_t chunkSize;
    uint8_t *verifyBuffer;
    uint8_t *progBuffer = NULL;
    uint16_t i;
    uint8_t j;
    if (verify)
        verifyBuffer = (uint8_t *)malloc(MPU6050_DMP_MEMORY_CHUNK_SIZE);
    if (useProgMem)
        progBuffer = (uint8_t *)malloc(MPU6050_DMP_MEMORY_CHUNK_SIZE);
    for (i = 0; i < dataSize;)
    {
        chunkSize = MPU6050_DMP_MEMORY_CHUNK_SIZE;

        if (i + chunkSize > dataSize)
            chunkSize = dataSize - i;

        if (chunkSize > 256 - address)
            chunkSize = 256 - address;
        
        if (useProgMem)
            for (j = 0; j < chunkSize; j++)
                progBuffer[j] = pgm_read_byte(data + i + j);
        else
            progBuffer = (uint8_t *)data + i;
    
        i2cWriteBytes(MPU6050_RA_MEM_R_W, chunkSize, progBuffer);

        if (verify && verifyBuffer)
        {
            setMemoryBank(bank);
            i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &address); // Set memory start address
            i2cReadBytes(MPU6050_RA_MEM_R_W, chunkSize, verifyBuffer);
            if (memcmp(progBuffer, verifyBuffer, chunkSize) != 0)
            {
                free(verifyBuffer);
                if (useProgMem)
                    free(progBuffer);
                return false;
            }
        }

        i += chunkSize;
        address += chunkSize;

        if (i < dataSize)
        {
            if (address == 0)
                bank++;
            setMemoryBank(bank);
            i2cWriteBytes(MPU6050_RA_MEM_START_ADDR, 1, &address); // Set memory start address
        }
    }
    if (verify)
        free(verifyBuffer);
    if (useProgMem)
        free(progBuffer);
    return true;
}

bool Accelerometer::writeDMPConfigurationSet(const uint8_t *data, uint16_t dataSize, bool useProgMem)
{
    uint8_t *progBuffer = NULL, success, special;
    uint16_t i, j;
    if (useProgMem)
        progBuffer = (uint8_t *)malloc(8);

    uint8_t bank, offset, length;
    for (i = 0; i < dataSize;)
    {
        if (useProgMem)
        {
            bank = pgm_read_byte(data + i++);
            offset = pgm_read_byte(data + i++);
            length = pgm_read_byte(data + i++);
        } else
        {
            bank = data[i++];
            offset = data[i++];
            length = data[i++];
        }

        if (length > 0)
        {
            if (useProgMem)
            {
                if (sizeof(progBuffer) < length)
                    progBuffer = (uint8_t *)realloc(progBuffer, length);
                for (j = 0; j < length; j++)
                    progBuffer[j] = pgm_read_byte(data + i + j);
            } else
                progBuffer = (uint8_t *)data + i;
            
            success = writeMemoryBlock(progBuffer, length, bank, offset, true);
            i += length;
        } else {
            if (useProgMem)
                special = pgm_read_byte(data + i++);
            else
                special = data[i++];

            if (special == 0x01)
            {
                uint8_t value = 0x32;
                i2cWriteBytes(MPU6050_RA_INT_ENABLE, 1, &value);
                success = true;
            }
            else
                success = false;
        }
        
        if (!success)
        {
            if (useProgMem)
                free(progBuffer);
            return false;
        }
    }
    if (useProgMem)
        free(progBuffer);
    return true;
}

int8_t Accelerometer::i2cReadBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout)
{
    uint8_t count, b;
    if ((count = i2cReadBytes(regAddr, 1, &b, timeout)) != 0)
    {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

int8_t Accelerometer::i2cReadBytes(uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout)
{
    int8_t count = 0;
    if (write(m_i2cfd, &regAddr, 1) != 1)
    {
        fprintf(stderr, "Failed to write reg: %s\n", strerror(errno));
        return(-1);
    }
    count = read(m_i2cfd, data, length);
    if (count < 0)
    {
        fprintf(stderr, "Failed to read device(%d): %s\n", count, ::strerror(errno));
        return(-1);
    }
    else if (count != length)
    {
        fprintf(stderr, "Short read  from device, expected %d, got %d\n", length, count);
        return(-1);
    }

    return count;
}

bool Accelerometer::i2cWriteBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
    uint8_t b;
    if (i2cReadBytes(regAddr, 1, &b) != 0)
    {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1);
        data &= mask;
        b &= ~(mask);
        b |= data;
        return i2cWriteBytes(regAddr, 1, &b);
    }
    else
        return false;
}

bool Accelerometer::i2cWriteBytes(uint8_t regAddr, uint8_t length, uint8_t* data)
{
    int8_t count = 0;
    uint8_t buf[128];

    if (length > 127)
    {
        fprintf(stderr, "Byte write count (%d) > 127\n", length);
        return(false);
    }

    buf[0] = regAddr;
    memcpy(buf+1,data,length);
    count = write(m_i2cfd, buf, length+1);
    if (count < 0)
    {
        fprintf(stderr, "Failed to write device(%d): %s\n", count, ::strerror(errno));
        return(false);
    }
    else if (count != length+1)
    {
        fprintf(stderr, "Short write to device, expected %d, got %d\n", length+1, count);
        return(false);
    }

    return true;
}

bool Accelerometer::i2cWriteWords(uint8_t regAddr, uint8_t length, uint16_t* data)
{
    int8_t count = 0;
    uint8_t buf[128];

    if (length > 63)
    {
        fprintf(stderr, "Word write count (%d) > 63\n", length);
        return(false);
    }
    buf[0] = regAddr;
    for (int i = 0; i < length; i++)
    {
        buf[i*2+1] = data[i] >> 8;
        buf[i*2+2] = data[i];
    }
    count = write(m_i2cfd, buf, length*2+1);
    if (count < 0)
    {
        fprintf(stderr, "Failed to write device(%d): %s\n", count, ::strerror(errno));
        return(false);
    }
    else if (count != length*2+1)
    {
        fprintf(stderr, "Short write to device, expected %d, got %d\n", length+1, count);
        return(false);
    }
    return true;
}
