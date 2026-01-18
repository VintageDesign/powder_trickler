#pragma once

#include <QObject>
#include <string>

class AbstractControllerInterface : public QObject
{
    Q_OBJECT

public:

    using QObject::QObject;

    explicit AbstractControllerInterface(QObject *parent = nullptr)
        : QObject(parent) {}
    virtual ~AbstractControllerInterface() {}

    virtual void send(const std::string &message) = 0;

signals:
    void receive(const std::string &message);
};
