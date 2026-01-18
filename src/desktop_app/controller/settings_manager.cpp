#include "settings_manager.h"
#include "interfaces/uart_interface.h"

#include <QSerialPortInfo>
#include <QDebug>

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
{
}

SettingsManager::~SettingsManager() = default;

std::shared_ptr<UartInterface> SettingsManager::getUartInterface() const
{
    return m_uartInterface;
}

void SettingsManager::refreshPorts()
{
    QStringList ports;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    qDebug() << "Available Ports:";
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                     ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                     : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                     ? QByteArray::number(portInfo.productIdentifier(), 16)
                     : QByteArray());
    }

    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        ports.append(portInfo.portName());
    }

    if (m_availablePorts != ports) {
        m_availablePorts = ports;
        qDebug() << "Ports list changed";
        emit availablePortsChanged(m_availablePorts);
    }
}

void SettingsManager::selectPort(const QString &port)
{
    if (m_selectedPort == port)
        return;

    m_selectedPort = port;
    emit selectedPortChanged(m_selectedPort);
}

void SettingsManager::connectToSelectedPort()
{
    if (m_selectedPort.isEmpty())
        return;

    if (m_uartInterface && m_uartInterface->isOpen()) {
        m_uartInterface->close();
    }

    m_uartInterface = std::make_shared<UartInterface>();

    QString fullPortPath = m_selectedPort;
    if (!fullPortPath.startsWith("/dev/")) {
        fullPortPath = "/dev/" + m_selectedPort;
    }

    if (m_uartInterface->open(fullPortPath)) {
        emit connectionStatusChanged(true);
        emit uartInterfaceCreated(m_uartInterface);
    } else {
        m_uartInterface.reset();
        emit connectionStatusChanged(false);
    }
}

void SettingsManager::disconnectFromPort()
{
    if (m_uartInterface) {
        m_uartInterface->close();
        m_uartInterface.reset();
    }
    emit connectionStatusChanged(false);
}
