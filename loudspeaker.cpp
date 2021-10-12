#include "loudspeaker.h"

Loudspeaker::Loudspeaker(qreal x, qreal y, QObject *parent) : QObject(parent), m_x(x), m_y(y)
{

}

qreal Loudspeaker::x() const
{
    return m_x;
}

void Loudspeaker::setX(const qreal &x)
{
    m_x = x;
}

qreal Loudspeaker::y() const
{
    return m_y;
}

void Loudspeaker::setY(const qreal &y)
{
    m_y = y;
}

qreal Loudspeaker::level() const
{
    return m_level;
}

void Loudspeaker::setLevel(const qreal &level)
{
    m_level = level;
}

qreal Loudspeaker::dB() const
{
    return 20.0 * std::log(m_level);
}

void Loudspeaker::setDb(qreal &value)
{
    setLevel(std::pow(10, value / 20.0));
}
