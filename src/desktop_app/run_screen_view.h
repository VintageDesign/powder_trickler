#ifndef RUN_SCREEN_VIEW_H
#define RUN_SCREEN_VIEW_H

#include <QObject>
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
    void setSetpoint(double value);

    QString actualValue() const;
    void setActualValue(double value);

public slots:
    void increment();
    void decrement();
    void dispense();

signals:
    void setpointChanged();
    void actualValueChanged();

private:
    double m_setpoint = 0.0;
    double m_actualValue = 0.0;
};

#endif // RUN_SCREEN_VIEW_H
