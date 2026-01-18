#include "qml/run_screen_view.h"

RunScreenView::RunScreenView(QObject *parent)
    : QObject(parent)
{
}

QString RunScreenView::setpoint() const
{
    return m_setpoint;
}

QString RunScreenView::actualValue() const
{
    return m_actualValue;
}

void RunScreenView::onSetpointChanged(double value)
{
    QString strValue = QString::number(value, 'f', 1);
    if (m_setpoint == strValue)
        return;

    m_setpoint = strValue;
    emit setpointChanged();
}

void RunScreenView::onActualValueChanged(double value)
{
    QString strValue = QString::number(value, 'f', 1);
    if (m_actualValue == strValue)
        return;

    m_actualValue = strValue;
    emit actualValueChanged();
}

void RunScreenView::increment()
{
    emit incrementRequested();
}

void RunScreenView::decrement()
{
    emit decrementRequested();
}

void RunScreenView::dispense()
{
    emit dispenseRequested();
}

void RunScreenView::setSetpointInput(const QString &value)
{
    bool ok;
    double doubleValue = value.toDouble(&ok);
    if (ok) {
        emit setpointInputRequested(doubleValue);
    }
}
