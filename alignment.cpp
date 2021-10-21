#include "alignment.h"
#include <complex>
#include <QtDebug>

Alignment::Alignment(QObject *parent) : QObject(parent),
    m_audience(this), m_environment(this),
    m_mains(0, 7, this), m_subwoofer(0, 0, this),

    m_axisData()
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

const Alignment::AxisData &Alignment::phase() const
{
    return m_axisData;
}

Alignment::DataPoint Alignment::calculate(qreal x, qreal y, qreal z) const noexcept
{
    auto mainsD = std::sqrt(
                      std::pow(x - m_mains.x(), 2) +
                      std::pow(y - m_mains.y(), 2) +
                      std::pow(z - m_mains.z(), 2)
                  );

    auto subsD = std::sqrt(
                     std::pow(x - m_subwoofer.x(), 2) +
                     std::pow(y - m_subwoofer.y(), 2) +
                     std::pow(z - m_subwoofer.z(), 2)
                 );

    auto delta = subsD - mainsD;
    auto dt = delta / m_environment.speedOfSound();
    auto phase = dt * m_frequency * 360.;

    auto mainsSPL = 20 * std::log10(ZERODB_DISSTANCE / mainsD) + m_mains.dB();
    auto subwooferSPL = 20 * std::log10(ZERODB_DISSTANCE / subsD) + m_subwoofer.dB();

    phase -= m_phaseOffset - m_maxPhaseOffset;
    mainsSPL -= m_levelOffset;
    subwooferSPL -= m_levelOffset;

    auto a = std::pow(10., mainsSPL / 20.);
    auto b = std::pow(10., subwooferSPL / 20.);
    auto alpha = M_PI * phase / 180;
    std::complex<qreal> ca = {a, 0};
    std::complex<qreal> cb = {b *std::cos(alpha), b *std::sin(alpha)};

    auto cs = ca + cb;
    return {
        {
            mainsSPL,
            subwooferSPL,
            20. * std::log10(std::abs(cs))
        },
        phase
    };
}

std::pair<Alignment::LevelZone, Alignment::PhaseZone> Alignment::zone(qreal x, qreal y, qreal z) const noexcept
{
    std::pair<Alignment::LevelZone, Alignment::PhaseZone> zones;
    auto data = calculate(x, y, z);

    auto diff = std::abs(data.spl.mains - data.spl.subwoofer);
    if (diff < 4) {
        zones.first = LevelZone::Combing;
    } else if (diff < 10) {
        zones.first = LevelZone::Combining;
    } else {
        zones.first = LevelZone::Isolation;
    }

    if (std::abs(data.phase) < 120) {
        zones.second = PhaseZone::Coupling;
    } else {
        zones.second = PhaseZone::Cancellation;
    }

    return zones;
}

void Alignment::update()
{
    updateOnax();

    emit ready();
}

void Alignment::updateOnax()
{
    auto const &a = m_audience.start();
    auto const &b = m_audience.stop();
    auto points = std::ceil(std::abs(b.x() - a.x()) / m_accuracy);
    auto x = a.x();

    m_axisData.resize(points);
    m_phaseOffset = -std::numeric_limits<qreal>::infinity();
    m_levelOffset = -std::numeric_limits<qreal>::infinity();

    auto i = 0;
    auto k = (b.y() - a.y()) / (b.x() - a.x());
    auto c = a.y() - a.x() * k;

    while (x < b.x()) {
        auto y = k * x + c;
        QPointF position(x, y);

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

        auto phase = dt * m_frequency * 360.;

        auto mainsSPL = 20 * std::log10(ZERODB_DISSTANCE / mainsD) + m_mains.dB();
        auto subwooferSPL = 20 * std::log10(ZERODB_DISSTANCE / subsD) + m_subwoofer.dB();

        m_axisData[i] = {x, phase, {mainsSPL, subwooferSPL, 0}};

        m_phaseOffset = std::max(m_phaseOffset, phase);
        m_levelOffset = std::max(m_levelOffset, mainsSPL);
        m_levelOffset = std::max(m_levelOffset, subwooferSPL);

        x += m_accuracy;
        ++i;
    }

    std::for_each(m_axisData.begin(), m_axisData.end(), [&](auto & el) {
        el.phase -= m_phaseOffset - m_maxPhaseOffset;
        el.spl.mains -= m_levelOffset;
        el.spl.subwoofer -= m_levelOffset;

        auto a = std::pow(10., el.spl.mains / 20.);
        auto b = std::pow(10., el.spl.subwoofer / 20.);
        auto alpha = M_PI * el.phase / 180;
        std::complex<qreal> ca = {a, 0};
        std::complex<qreal> cb = {b *std::cos(alpha), b *std::sin(alpha)};

        auto cs = ca + cb;
        el.spl.sum = 20. * std::log10(std::abs(cs));
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

