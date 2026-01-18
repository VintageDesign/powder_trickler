#include "run_screen_view.h"

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

void RunScreenView::onSetpointChanged(const QString &value)
{
    if (m_setpoint == value)
        return;

    m_setpoint = value;
    emit setpointChanged();
}

void RunScreenView::onActualValueChanged(const QString &value)
{
    if (m_actualValue == value)
        return;

    m_actualValue = value;
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
