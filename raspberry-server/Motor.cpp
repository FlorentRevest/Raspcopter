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

#include "Motor.h"

Motor::Motor(unsigned char channel)
{
	m_channel = channel;
}

int Motor::getSpeed()
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd == -1)
    	return -1;

    struct termios options;
    tcgetattr(fd, &options);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    options.c_oflag &= ~(ONLCR | OCRNL);
    tcsetattr(fd, TCSANOW, &options);

    unsigned char command[] = {0x90, m_channel};
    if(write(fd, command, sizeof(command)) == -1)
        return -1;

    unsigned char response[2];
    if(read(fd,response,2) != 2)
        return -1;

    close(fd);
    return response[0] + 256*response[1];
}
 
bool Motor::setSpeed(unsigned short target)
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd == -1)
    	return -1;

    struct termios options;
    tcgetattr(fd, &options);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    options.c_oflag &= ~(ONLCR | OCRNL);
    tcsetattr(fd, TCSANOW, &options);

    unsigned char command[] = {0x84, m_channel, target & 0x7F, target >> 7 & 0x7F};
    if(write(fd, command, sizeof(command)) == -1)
        return false;
    return true;
}

