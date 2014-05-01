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
