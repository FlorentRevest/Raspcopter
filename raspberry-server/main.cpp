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

#include <cstdint>

#include "Accelerometer.h"
#include "PID.h"
#include "Motors.h"
#include "Logger.h"

// TODO: Calibrate the horizontal values with 6 seconds mesurements
// TODO: Logger class -> exports csv
// TODO: Network class
// TODO: Signals handler
// TODO: Compute motor speed from PIDs sum

int main()
{
    Accelerometer mpu;
    PID y_pid(1, 0, 0);
    PID p_pid(1, 0, 0);
    PID r_pid(1, 0, 0);
    Motors motors;
    Logger logger;

    usleep(100000);

    uint8_t fifoBuffer[64];
    Quaternion q;
    VectorFloat gravity;
    float ypr[3], y_target = 0, p_target = 0, r_target = 0;
    uint16_t packetSize = mpu.getFIFOPacketSize();

    while(true) {
        uint16_t fifoCount = mpu.getFIFOCount();
        if (fifoCount == 1024)
            mpu.resetFIFO(); // FIFO overflow
        else if (fifoCount >= 42) {
            mpu.getFIFOBytes(fifoBuffer, packetSize);
            mpu.getQuaternion(&q, fifoBuffer);
            mpu.getGravity(&gravity, &q);
            mpu.getYawPitchRoll(ypr, &q, &gravity);

            float y = ypr[0] * 180/M_PI, p  = ypr[1] * 180/M_PI, r = ypr[2] * 180/M_PI;
            float y_computed = y_pid.compute(y, y_target), p_computed = p_pid.compute(p, p_target), r_computed = r_pid.compute(r, r_target);

            std::cout << "y=" << y_computed << ", p=" << p_computed << ", r=" << r_computed << std::endl;
        }
    }

    motors.safeLand();
    exit(EXIT_SUCCESS);
}

