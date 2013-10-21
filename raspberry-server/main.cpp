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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "Accelerometer.h"

int main()
{
    Accelerometer mpu;
    if(mpu.isConnected())
        printf("MPU6050 is alright !\n");
    else
    {
        printf("MPU6050 got a problem.\n");
        return 1;
    }
    mpu.setDMPEnabled(true);

    uint16_t packetSize = mpu.getFIFOPacketSize();
    uint8_t fifoBuffer[64];

    Quaternion q;
    VectorFloat gravity;
    float ypr[3];

    usleep(100000);

    while(true)
    {
        uint16_t fifoCount = mpu.getFIFOCount();

        if (fifoCount == 1024)
        {
            mpu.resetFIFO();
            printf("FIFO overflow!\n");
        }
        else if (fifoCount >= 42)
        {
            mpu.getFIFOBytes(fifoBuffer, packetSize);
        
            mpu.getQuaternion(&q, fifoBuffer);
            printf("quat %7.2f %7.2f %7.2f %7.2f    ", q.w,q.x,q.y,q.z);
            mpu.getGravity(&gravity, &q);
            mpu.getYawPitchRoll(ypr, &q, &gravity);
            printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
            printf("\n");
        }
    }

    return 0;
}
