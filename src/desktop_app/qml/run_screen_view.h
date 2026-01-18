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
    void onSetpointChanged(double value);
    void onActualValueChanged(double value);

    void increment();
    void decrement();
    void dispense();
    void setSetpointInput(const QString &value);

signals:
    void setpointChanged();
    void actualValueChanged();

    void incrementRequested();
    void decrementRequested();
    void dispenseRequested();
    void setpointInputRequested(double value);

private:
    QString m_setpoint = "0.0";
    QString m_actualValue = "0.0";
};

#endif // RUN_SCREEN_VIEW_H
