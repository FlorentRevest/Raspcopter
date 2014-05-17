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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>

#define JS_EVENT_BUTTON 0x01
#define JS_EVENT_AXIS   0x02
#define JS_EVENT_INIT   0x80

class JoystickEvent
{
public:
    unsigned int time;
    short value;
    unsigned char type;
    unsigned char number;
    bool isButton() {
        return (type & JS_EVENT_BUTTON) != 0;
    }
    bool isAxis() {
        return (type & JS_EVENT_AXIS) != 0;
    }
    bool isInitialState() {
        return (type & JS_EVENT_INIT) != 0;
    }
};

class Joystick
{
public:
    ~Joystick();
    Joystick(std::string devicePath);
    bool isFound();
    bool sample(JoystickEvent* event);

private:
    void openPath(std::string devicePath);
    int _fd;
};

#endif // JOYSTICK_H
