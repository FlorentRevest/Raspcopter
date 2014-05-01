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
