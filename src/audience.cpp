#include "audience.h"

Audience::Audience(QObject *parent) : QObject(parent), m_start(5, 1.8), m_stop(60, 1.8)
{
    connect(this, &Audience::startChanged, [this]() {
        emit changed();
    });
    connect(this, &Audience::stopChanged, [this]() {
        emit changed();
    });
}

QPointF &Audience::start() noexcept
{
    return m_start;
}

const QPointF &Audience::start() const noexcept
{
    return m_start;
}

void Audience::setStart(const QPointF &start) noexcept
{
    if (m_start != start) {
        m_start = start;
        emit startChanged(m_start);
    }
}

QPointF &Audience::stop() noexcept
{
    return m_stop;
}

const QPointF &Audience::stop() const noexcept
{
    return m_stop;
}

void Audience::setStop(const QPointF &stop) noexcept
{
    if (m_stop != stop) {
        m_stop = stop;
        emit stopChanged(m_stop);
    }
}
