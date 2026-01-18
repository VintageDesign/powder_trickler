#pragma once

#include <QObject>
#include <QString>
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

signals:
    void setpointChanged(const QString &value);
    void actualValueChanged(const QString &value);

private:
    std::shared_ptr<AbstractControllerInterface> _controller;
    double _setpoint_value = 0.0;
    double _actual_value = 0.0;
};
