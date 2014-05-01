/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2014 - Florent Revest <florent.revest666@gmail.com>
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
#include "Network.h"

// TODO: Calibrate the horizontal values with 6 seconds mesurements
// TODO: Logger class
// TODO: Signals handler

PID y_pid(2,0,0), p_pid(2,0,0), r_pid(2,0,0);
float y_target = 0, p_target = 0, r_target = 0, throttle = 0;

int main()
{
    Network network;
    Accelerometer mpu;
    Motors motors;
    motors.setToZero();

    while(true) {
        if(mpu.getFIFOCount() > 42) {
            float ypr[3];
            mpu.getYawPitchRoll(ypr);

            network.send(SET_MEASURED_VALUES, ypr, sizeof(float)*3, false);

            float /*y = ypr[0] * 180/M_PI,*/ p  = ypr[1] * 180/M_PI, r = ypr[2] * 180/M_PI;
            float /*y_computed = y_pid.compute(y, y_target),*/ p_computed = p_pid.compute(p, p_target), r_computed = r_pid.compute(r, r_target);

            motors.setSpeed(MOTOR_FL, throttle + p_computed - r_computed); // Note: Pitch and Roll are reversed on my quadcopter it's my fault
            motors.setSpeed(MOTOR_BL, throttle + p_computed + r_computed);
            motors.setSpeed(MOTOR_FR, throttle - p_computed - r_computed);
            motors.setSpeed(MOTOR_BR, throttle - p_computed + r_computed);
        }
    } 

    exit(EXIT_SUCCESS);
}

