#include "loudspeaker.h"

Loudspeaker::Loudspeaker(qreal x, qreal y, QObject *parent) : QObject(parent), m_x(x), m_y(y)
{
    connect(this, &Loudspeaker::xChanged, [this]() {
        emit changed();
    });
    connect(this, &Loudspeaker::yChanged, [this]() {
        emit changed();
    });
    connect(this, &Loudspeaker::levelChanged, [this]() {
        emit changed();
    });
}

qreal Loudspeaker::x() const noexcept
{
    return m_x;
}

void Loudspeaker::setX(const qreal &x) noexcept
{
    if (!qFuzzyCompare(m_x, x)) {
        m_x = x;
        emit xChanged(m_x);
    }
}

qreal Loudspeaker::y() const noexcept
{
    return m_y;
}

void Loudspeaker::setY(const qreal &y) noexcept
{
    if (!qFuzzyCompare(m_y, y)) {
        m_y = y;
        emit yChanged(m_y);
    }
}

qreal Loudspeaker::level() const noexcept
{
    return m_level;
}

void Loudspeaker::setLevel(const qreal &level) noexcept
{
    if (!qFuzzyCompare(m_level, level)) {
        m_level = level;
        emit levelChanged(m_level);
    }
}

qreal Loudspeaker::dB() const
{
    return 20.0 * std::log10(m_level);
}

void Loudspeaker::setDb(qreal &value)
{
    setLevel(std::pow(10, value / 20.0));
}
