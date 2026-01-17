#include "run_screen_view.h"

RunScreenView::RunScreenView(QObject *parent)
    : QObject(parent)
{
}

QString RunScreenView::setpoint() const
{
    return QString::number(m_setpoint);
}

void RunScreenView::setSetpoint(double value)
{
    if (qFuzzyCompare(m_setpoint, value))
        return;
    m_setpoint = value;

    if(m_setpoint < 0)
        m_setpoint = 0;
    emit setpointChanged();
}

QString RunScreenView::actualValue() const
{
    return QString::number(m_actualValue);
}

void RunScreenView::setActualValue(double value)
{
    if (qFuzzyCompare(m_actualValue, value))
        return;

    m_actualValue = value;
    emit actualValueChanged();
}

void RunScreenView::increment()
{
    setSetpoint(m_setpoint + 0.1);
}

void RunScreenView::decrement()
{
    setSetpoint(m_setpoint - 0.1);
}

void RunScreenView::dispense()
{
    // TODO: Implement dispense logic
}
