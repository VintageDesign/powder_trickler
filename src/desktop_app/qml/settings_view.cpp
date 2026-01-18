#include "qml/settings_view.h"
#include <QDebug>

SettingsView::SettingsView(QObject *parent)
    : QObject(parent)
{
}

QStringList SettingsView::availablePorts() const
{
    return m_availablePorts;
}

QString SettingsView::selectedPort() const
{
    return m_selectedPort;
}

bool SettingsView::isConnected() const
{
    return m_isConnected;
}

void SettingsView::onAvailablePortsChanged(const QStringList &ports)
{
    if (m_availablePorts == ports)
    {
        qDebug() << "Skipping. Ports list hasn't changed";
        return;
    }

    m_availablePorts = ports;
    emit availablePortsChanged();
}

void SettingsView::onSelectedPortChanged(const QString &port)
{
    if (m_selectedPort == port)
        return;

    m_selectedPort = port;
    emit selectedPortChanged();
}

void SettingsView::onConnectionStatusChanged(bool connected)
{
    if (m_isConnected == connected)
        return;

    m_isConnected = connected;
    emit isConnectedChanged();
}

void SettingsView::refreshPorts()
{
    emit refreshPortsRequested();
}

void SettingsView::selectPort(const QString &port)
{
    emit portSelectionRequested(port);
}

void SettingsView::connectToPort()
{
    emit connectRequested();
}

void SettingsView::disconnect()
{
    emit disconnectRequested();
}
