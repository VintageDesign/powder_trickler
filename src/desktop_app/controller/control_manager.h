#pragma once

#include <QObject>

#include <interfaces/abstract_controller_interface.h>
#include <run_screen_view.h>

class ControlManager: public QObject
{
    Q_OBJECT
    public:
        ControlManager(const std::shared_ptr<AbstractControllerInterface> &controller);

    public slots:
        void increment();
        void decrement();
        void dispense();

    signals:
        void setpointChanged(double value);
        void actualValueChanged(double value);

    private:
        std::shared_ptr<AbstractControllerInterface> _controller;
        double _setpoint_value = 0;
        double _actual_value = 0;


};
