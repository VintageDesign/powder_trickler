#pragma once

#include <QObject>
#include <memory>

#include <interfaces/abstract_controller_interface.h>


class ControlManager : public QObject
{
    Q_OBJECT

public:
    explicit ControlManager(const std::shared_ptr<AbstractControllerInterface> &controller,
                            QObject *parent = nullptr);

public slots:
    void increment();
    void decrement();
    void dispense();
    void setSetpoint(double value);

signals:
    void setpointChanged(double value);
    void actualValueChanged(double value);

private:
    std::shared_ptr<AbstractControllerInterface> _controller;
    double _setpoint_value = 0.0;
    double _actual_value = 0.0;
};
