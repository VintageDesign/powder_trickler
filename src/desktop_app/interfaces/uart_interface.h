#pragma once

#include "abstract_controller_interface.h"

#include <QSerialPort>
#include <QByteArray>
#include <QString>

class UartInterface : public AbstractControllerInterface
{
    Q_OBJECT

public:
    explicit UartInterface(QObject *parent = nullptr);
    ~UartInterface() override;

    bool open(const QString &portName, qint32 baudRate = QSerialPort::Baud115200);
    void close();
    bool isOpen() const;

    void send(const std::string &message) override;

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
    QByteArray m_readBuffer;
};
