/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2014 - Florent Revest <florent.revest666@gmail.com>

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

#include "Motors.h"

Motors::Motors()
{
    ctx = 0;
    libusb_init(&ctx);
    libusb_device **device_list = 0;
    int count = libusb_get_device_list(ctx, &device_list);

    for(int i=0 ; i < count ; i++) {
        libusb_device *device = device_list[i];
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);

        if(desc.idVendor == 0x1ffb && desc.idProduct == 0x0089) {
            libusb_open(device, &device_handle);
            break;
        }
    }

    libusb_free_device_list(device_list, 0);

    for(int i=0 ; i<6 ; i++)
        speeds[i] = 0;
}

unsigned short Motors::getSpeed(unsigned char channel)
{
    return speeds[channel];
}

void Motors::setSpeed(unsigned char channel, unsigned short target)
{
    libusb_control_transfer(device_handle, 0x40, 0x85, 1225 + target*4, channel, 0, 0, (ushort)5000);
    speeds[channel] = target;
}

void Motors::setToZero()
{
    setSpeed(MOTOR_FL, 0);
    setSpeed(MOTOR_FR, 0);
    setSpeed(MOTOR_BL, 0);
    setSpeed(MOTOR_BR, 0);
}

Motors::~Motors()
{
    libusb_close(device_handle);
    libusb_exit(ctx);
}

