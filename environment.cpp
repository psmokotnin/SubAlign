#include "environment.h"

Environment::Environment(QObject *parent) : QObject(parent)
{
    connect(this, &Environment::temperatureChanged, [this]() {
        emit changed();
    });
}

qreal Environment::temperature() const
{
    return m_temperature;
}

void Environment::setTemperature(const qreal &temperature)
{
    if (!qFuzzyCompare(m_temperature, temperature)) {
        m_temperature = temperature;
        emit temperatureChanged(m_temperature);
    }
}

qreal Environment::speedOfSound() const noexcept
{
    return 20.05 * std::sqrt(273.15 + m_temperature);
}
