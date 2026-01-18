#include "uart_interface.h"

#include <QDebug>

UartInterface::UartInterface(QObject *parent)
    : AbstractControllerInterface(parent)
{
    connect(&m_serialPort, &QSerialPort::readyRead, this, &UartInterface::onReadyRead);
    connect(&m_serialPort, &QSerialPort::errorOccurred, this, &UartInterface::onErrorOccurred);
}

UartInterface::~UartInterface()
{
    close();
}

bool UartInterface::open(const QString &portName, qint32 baudRate)
{
    if (m_serialPort.isOpen()) {
        close();
    }

    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(baudRate);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort.open(QIODevice::ReadWrite)) {
        qWarning() << "Failed to open serial port:" << portName << m_serialPort.errorString();
        return false;
    }

    m_readBuffer.clear();
    return true;
}

void UartInterface::close()
{
    if (m_serialPort.isOpen()) {
        m_serialPort.close();
    }
    m_readBuffer.clear();
}

bool UartInterface::isOpen() const
{
    return m_serialPort.isOpen();
}

void UartInterface::send(const std::string &message)
{
    if (!m_serialPort.isOpen()) {
        qWarning() << "Cannot send: serial port is not open";
        return;
    }

    QByteArray data = QByteArray::fromStdString(message);
    qint64 bytesWritten = m_serialPort.write(data);

    if (bytesWritten != data.size()) {
        qWarning() << "Failed to write all data to serial port";
    }
}

void UartInterface::onReadyRead()
{
    m_readBuffer.append(m_serialPort.readAll());

    int newlineIndex;
    while ((newlineIndex = m_readBuffer.indexOf('\n')) != -1) {
        QByteArray line = m_readBuffer.left(newlineIndex);
        m_readBuffer.remove(0, newlineIndex + 1);

        emit receive(line.toStdString());
    }
}

void UartInterface::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        qWarning() << "Serial port error:" << error << m_serialPort.errorString();
    }
}
