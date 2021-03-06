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
#include <csignal>

#include "Accelerometer.h"
#include "PID.h"
#include "Motors.h"
#include "Logger.h"
#include "Network.h"

// TODO: Logger class

void sigHandler(int sig);
PID y_pid(2,0,0), p_pid(2,0,0), r_pid(2,0,0);
float y_target = 0, p_target = 0, r_target = 0, throttle = 0;
Motors motors;

int main()
{
    Network network;
    Accelerometer imu;
    imu.bypassDrift();
    motors.setToZero();

    signal(SIGABRT, sigHandler);
    signal(SIGINT, sigHandler);
    signal(SIGKILL, sigHandler);
    signal(SIGQUIT, sigHandler);
    signal(SIGTERM, sigHandler);

    float ypr[3];
    while(true) {
        if(imu.getFIFOCount() > 42) {
            imu.getYawPitchRoll(ypr);

            float p_computed = p_pid.compute(ypr[1], p_target), r_computed = r_pid.compute(ypr[2], r_target);
            motors.setSpeed(MOTOR_FL, throttle + r_computed - p_computed);
            motors.setSpeed(MOTOR_BL, throttle + r_computed + p_computed);
            motors.setSpeed(MOTOR_FR, throttle - r_computed - p_computed);
            motors.setSpeed(MOTOR_BR, throttle - r_computed + p_computed);

            network.send(SET_MEASURED_VALUES, ypr, sizeof(float)*3, false);
        }
    } 

    exit(EXIT_SUCCESS);
}

void sigHandler(int sig)
{
    std::cout << "[ERROR] Received signal " << sig << std::endl;
    motors.setToZero();
    exit(sig);
}

