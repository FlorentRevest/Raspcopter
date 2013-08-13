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

#include <iostream>
#include "Accelerometer.h"

int main(int argc, char *argv[])
{
    Accelerometer *accel= new Accelerometer(); // Initialize the MPU6050
    if(accel->isConnected())
    	std::cout << "Accelerometer initialisation successful." << std::endl;
    else
    {
    	std::cout << "Accelerometer initialisation error... Abort" << std::endl;
    	return 1;
    }

    while(1)
    {
   	    AccelGyroValues values = accel->getAccelGyroValues();
    	std::cout << "accelerometer: " << values.ax << values.ay << values.az << std::endl
    	          << "gyrometer: " << values.gx << values.gy << values.gz << std::endl;
    }
    return 0;
}
