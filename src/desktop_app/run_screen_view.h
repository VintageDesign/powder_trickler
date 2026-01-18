#ifndef RUN_SCREEN_VIEW_H
#define RUN_SCREEN_VIEW_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

class RunScreenView : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString setpoint READ setpoint NOTIFY setpointChanged)
    Q_PROPERTY(QString actualValue READ actualValue NOTIFY actualValueChanged)

public:
    explicit RunScreenView(QObject *parent = nullptr);

    QString setpoint() const;
    QString actualValue() const;

public slots:
    void onSetpointChanged(const QString &value);
    void onActualValueChanged(const QString &value);

    void increment();
    void decrement();
    void dispense();

signals:
    void setpointChanged();
    void actualValueChanged();

    void incrementRequested();
    void decrementRequested();
    void dispenseRequested();

private:
    QString m_setpoint = "0.0";
    QString m_actualValue = "0.0";
};

#endif // RUN_SCREEN_VIEW_H
