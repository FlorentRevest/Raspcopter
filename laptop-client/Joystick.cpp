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

#include "Joystick.h"

Joystick::Joystick(std::string devicePath)
{
    openPath(devicePath);
    JoystickEvent event;
    while (sample(&event)) ; // Ignore useless init event
}

void Joystick::openPath(std::string devicePath)
{
    _fd = open(devicePath.c_str(), O_RDONLY | O_NONBLOCK);
}

bool Joystick::sample(JoystickEvent* event)
{
    int bytes = read(_fd, event, sizeof(*event));

    if (bytes == -1)
        return false;

    return bytes == sizeof(*event);
}

bool Joystick::isFound()
{
    return _fd >= 0;
}

Joystick::~Joystick()
{
    close(_fd);
};
