#include "alignment.h"
#include <QtDebug>

Alignment::Alignment(QObject *parent) : QObject(parent), m_environment(this),
    m_subwoofer(1, 0), m_mains(0, 3.6)
{
}

qreal Alignment::maxPhaseOffset() const
{
    return m_maxPhaseOffset;
}

void Alignment::setMaxPhaseOffset(const qreal &maxPhaseOffset)
{
    if (!qFuzzyCompare(m_maxPhaseOffset, maxPhaseOffset)) {
        m_maxPhaseOffset = maxPhaseOffset;
        emit maxPhaseOffsetChanged(m_maxPhaseOffset);
    }
}

qreal Alignment::frequency() const
{
    return m_frequency;
}

void Alignment::setFrequency(const qreal &frequency)
{
    if (!qFuzzyCompare(m_frequency, frequency)) {
        m_frequency = frequency;
        emit frequencyChanged(m_frequency);
    }
}

Environment *Alignment::environment()
{
    return &m_environment;
}

Loudspeaker *Alignment::subwoofer()
{
    return &m_subwoofer;
}

Loudspeaker *Alignment::mains()
{
    return &m_mains;
}

Audience *Alignment::audience()
{
    return &m_audience;
}
