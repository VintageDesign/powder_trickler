#include "control_manager.h"

ControlManager::ControlManager(const std::shared_ptr<AbstractControllerInterface> &controller,
                               QObject *parent)
    : QObject(parent)
    , _controller(controller)
{
}

void ControlManager::increment()
{
    _setpoint_value += 0.1;
    emit setpointChanged(QString::number(_setpoint_value, 'f', 1));
}

void ControlManager::decrement()
{
    _setpoint_value -= 0.1;
    if (_setpoint_value < 0)
        _setpoint_value = 0;
    emit setpointChanged(QString::number(_setpoint_value, 'f', 1));
}

void ControlManager::dispense()
{
    // TODO: Implement dispense logic using _controller
}
