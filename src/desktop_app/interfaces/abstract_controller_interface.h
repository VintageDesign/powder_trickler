#pragma once

#include <QObject>

class AbstractControllerInterface : public QObject
{
    Q_OBJECT
    public:
        virtual ~AbstractControllerInterface();

        virtual void send(std::string message);

    signals:
        void receive(std::string message);

};
