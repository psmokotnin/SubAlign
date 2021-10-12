#include "audience.h"

Audience::Audience(QObject *parent) : QObject(parent), m_start(0, 1.8), m_stop(40, 1.8)
{

}

QPointF Audience::start() const
{
    return m_start;
}

void Audience::setStart(const QPointF &start)
{
    if (m_start != start) {
        m_start = start;
        emit startChanged(m_start);
    }
}

QPointF Audience::stop() const
{
    return m_stop;
}

void Audience::setStop(const QPointF &stop)
{
    if (m_stop != stop) {
        m_stop = stop;
        emit stopChanged(m_stop);
    }
}
