#include "control_manager.h"

ControlManager::ControlManager(const std::shared_ptr<AbstractControllerInterface> &controller)
    : QObject(nullptr)
    , _controller(controller)
{
}

void ControlManager::increment()
{
    _setpoint_value += 0.1;
    emit setpointChanged(_setpoint_value);
}

void ControlManager::decrement()
{
    _setpoint_value -= 0.1;
    if (_setpoint_value < 0)
        _setpoint_value = 0;
    emit setpointChanged(_setpoint_value);
}

void ControlManager::dispense()
{
    // TODO: Implement dispense logic using _controller
}
