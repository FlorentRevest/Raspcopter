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

#include "PID.h"

PID::PID(float p, float i, float d)
{
    kp = p;
    ki = i;
    kd = d;
    lastError = 0;
    integral = 0;

    gettimeofday(&tv, 0);
    lastTime = tv.tv_sec * 1000 + tv.tv_usec/1000.0 + 0.5;
}

void PID::setConstants(float p, float i, float d)
{
    kp = p;
    ki = i;
    kd = d;
}

float PID::compute(float input, float setpoint)
{
    gettimeofday(&tv, 0);
    long time = tv.tv_sec * 1000 + tv.tv_usec/1000.0 + 0.5;
    long deltaTime = time - lastTime;
    float error = setpoint - input;
    long deltaError = error - lastError;

    float proportional = error * kp;
    integral += error * deltaTime * ki;
    integral = std::min(integral, (float)5000);
    integral = std::max(integral, (float)-5000);
    float derivative = deltaError * kd / deltaTime;

    lastError = error;
    lastTime = time;

    return proportional + integral + derivative;
}

