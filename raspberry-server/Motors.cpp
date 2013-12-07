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

#include "Motors.h"

Motors::Motors()
{
    // Open the Pololu Maestro file descriptor
    m_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if(m_fd != -1)
        abort();

    struct termios options;
    tcgetattr(m_fd, &options);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    options.c_oflag &= ~(ONLCR | OCRNL);
    tcsetattr(m_fd, TCSANOW, &options);
}

unsigned short Motors::getSpeed(unsigned char channel)
{
    unsigned char command[] = {0x90, channel};
    if(write(m_fd, command, sizeof(command)) == -1)
        return -1;

    unsigned char response[2];
    if(read(m_fd, response, 2) != 2)
        return -1;

    return response[0] + 256*response[1];
}

bool Motors::setSpeed(unsigned char channel, unsigned short target)
{
    unsigned char command[] = {0x84, channel, (unsigned char)(target & 0x7F, target >> 7 & 0x7F)};
    if(write(m_fd, command, sizeof(command)) == -1)
        return false;
    return true;
}

void Motors::safeLand()
{
    // Not so safe for now...
    setSpeed(MOTOR_FL, 0);
    setSpeed(MOTOR_FR, 0);
    setSpeed(MOTOR_BL, 0);
    setSpeed(MOTOR_BR, 0);
}

Motors::~Motors()
{
    close(m_fd);
}

