#include "environment.h"

Environment::Environment(QObject *parent) : QObject(parent)
{

}

qreal Environment::temperature() const
{
    return m_temperature;
}

void Environment::setTemperature(const qreal &temperature)
{
    m_temperature = temperature;
}
