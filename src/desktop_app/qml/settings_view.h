#ifndef SETTINGS_VIEW_H
#define SETTINGS_VIEW_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QtQml/qqmlregistration.h>

class SettingsView : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QStringList availablePorts READ availablePorts NOTIFY availablePortsChanged)
    Q_PROPERTY(QString selectedPort READ selectedPort NOTIFY selectedPortChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)

public:
    explicit SettingsView(QObject *parent = nullptr);

    QStringList availablePorts() const;
    QString selectedPort() const;
    bool isConnected() const;

public slots:
    void onAvailablePortsChanged(const QStringList &ports);
    void onSelectedPortChanged(const QString &port);
    void onConnectionStatusChanged(bool connected);

    void refreshPorts();
    void selectPort(const QString &port);
    void connectToPort();
    void disconnect();

signals:
    void availablePortsChanged();
    void selectedPortChanged();
    void isConnectedChanged();

    void refreshPortsRequested();
    void portSelectionRequested(const QString &port);
    void connectRequested();
    void disconnectRequested();

private:
    QStringList m_availablePorts;
    QString m_selectedPort;
    bool m_isConnected = false;
};

#endif // SETTINGS_VIEW_H
