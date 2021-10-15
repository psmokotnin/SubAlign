#include "alignment.h"
#include <QtDebug>

Alignment::Alignment(QObject *parent) : QObject(parent),
    m_audience(this), m_environment(this),
    m_mains(0, 7, this), m_subwoofer(0, 0, this),

    m_phase()
{
    connect(&m_audience,    &Audience::changed,    [this]() {
        update();
    });
    connect(&m_environment, &Environment::changed, [this]() {
        update();
    });
    connect(&m_mains,       &Loudspeaker::changed, [this]() {
        update();
    });
    connect(&m_subwoofer,   &Loudspeaker::changed, [this]() {
        update();
    });

    update();
}

qreal Alignment::maxPhaseOffset() const noexcept
{
    return m_maxPhaseOffset;
}

void Alignment::setMaxPhaseOffset(const qreal &maxPhaseOffset)
{
    if (!qFuzzyCompare(m_maxPhaseOffset, maxPhaseOffset)) {
        m_maxPhaseOffset = maxPhaseOffset;
        emit maxPhaseOffsetChanged(m_maxPhaseOffset);
        update();
    }
}

qreal Alignment::frequency() const noexcept
{
    return m_frequency;
}

void Alignment::setFrequency(const qreal &frequency)
{
    if (!qFuzzyCompare(m_frequency, frequency)) {
        m_frequency = frequency;
        emit frequencyChanged(m_frequency);
        update();
    }
}

Environment *Alignment::environment() noexcept
{
    return &m_environment;
}

Loudspeaker *Alignment::subwoofer() noexcept
{
    return &m_subwoofer;
}

Loudspeaker *Alignment::mains() noexcept
{
    return &m_mains;
}

Audience *Alignment::audience() noexcept
{
    return &m_audience;
}

const Alignment::PhaseData &Alignment::phase() const
{
    return m_phase;
}

void Alignment::update()
{
    updatePhase();

    emit ready();
}

void Alignment::updatePhase()
{
    auto x = m_audience.start().x();
    auto end = m_audience.stop().x();
    auto points = std::ceil(std::abs(end - x) / m_accuracy);

    m_phase.resize(points);
    qreal offset = -std::numeric_limits<qreal>::infinity();
    auto i = 0;

    while (x < end) {
        auto value = phase(x);
        m_phase[i] = {x, value};
        if (offset < value) {
            offset = value;
        }

        x += m_accuracy;
        ++i;
    }
    std::for_each(m_phase.begin(), m_phase.end(), [&](auto & el) {
        el.second -= offset - m_maxPhaseOffset;
    });
}

qreal Alignment::phase(qreal x) const noexcept
{
    auto &a = m_audience.start();
    auto &b = m_audience.stop();

    auto k = (b.y() - a.y()) / (b.x() - a.x());
    auto y = k * x - a.x() * k + a.y();
    QPointF position(x, y);

    //d1
    auto mainsD = std::sqrt(
                      std::pow(position.x() - m_mains.x(), 2) +
                      std::pow(position.y() - m_mains.y(), 2)
                  );

    auto subsD = std::sqrt(
                     std::pow(position.x() - m_subwoofer.x(), 2) +
                     std::pow(position.y() - m_subwoofer.y(), 2)
                 );

    auto delta = subsD - mainsD;
    auto dt = delta / m_environment.speedOfSound();

    return dt * m_frequency * 360.0;
}

