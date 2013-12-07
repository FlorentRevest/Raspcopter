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


#ifndef PID_H
#define PID_H

#include <sys/time.h>
#include <algorithm>

class PID
{
public:
    PID(float p, float i, float d);
    void setConstants(float p, float i, float d);
    float compute(float input, float setpoint);

private:
    float kp, ki, kd, lastError, integral;
    long  lastTime;
    struct timeval tv;
};

#endif // PID_H

