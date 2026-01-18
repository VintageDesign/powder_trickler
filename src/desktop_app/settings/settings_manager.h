#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <memory>

class UartInterface;

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager();

    std::shared_ptr<UartInterface> getUartInterface() const;

public slots:
    void refreshPorts();
    void selectPort(const QString &port);
    void connectToSelectedPort();
    void disconnectFromPort();

signals:
    void availablePortsChanged(const QStringList &ports);
    void selectedPortChanged(const QString &port);
    void connectionStatusChanged(bool connected);
    void uartInterfaceCreated(std::shared_ptr<UartInterface> interface);

private:
    QStringList m_availablePorts;
    QString m_selectedPort;
    std::shared_ptr<UartInterface> m_uartInterface;
};
