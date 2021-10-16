#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <QtQml>

#include "environment.h"
#include "loudspeaker.h"
#include "audience.h"

class Alignment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal maxPhaseOffset READ maxPhaseOffset WRITE setMaxPhaseOffset NOTIFY maxPhaseOffsetChanged)
    Q_PROPERTY(qreal frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)
    Q_PROPERTY(Environment *environment READ environment CONSTANT)
    Q_PROPERTY(Loudspeaker *subwoofer READ subwoofer CONSTANT)
    Q_PROPERTY(Loudspeaker *mains READ mains CONSTANT)
    Q_PROPERTY(Audience *audience READ audience CONSTANT)
    QML_ELEMENT

    constexpr static const qreal ZERODB_DISSTANCE = 1.0;

public:
    explicit Alignment(QObject *parent = nullptr);
    struct AxisPoint {
        qreal x;
        qreal phase;

        struct {
            qreal mains;
            qreal subwoofer;
            qreal sum;
        } spl;
    };
    using AxisData = std::vector<AxisPoint>;

    qreal maxPhaseOffset() const noexcept;
    void setMaxPhaseOffset(const qreal &maxPhaseOffset);

    qreal frequency() const noexcept;
    void setFrequency(const qreal &frequency);

    Audience *audience() noexcept;
    Environment *environment() noexcept;
    Loudspeaker *mains() noexcept;
    Loudspeaker *subwoofer() noexcept;

    const AxisData &phase() const;

signals:
    void maxPhaseOffsetChanged(qreal);
    void frequencyChanged(qreal);
    void ready();

private:
    void update();

    void updateOnax();
    qreal phase(qreal x) const noexcept;

    qreal m_maxPhaseOffset = 0;
    qreal m_frequency = 100;
    qreal m_accuracy = 0.01;

    Audience m_audience;
    Environment m_environment;
    Loudspeaker m_mains, m_subwoofer;

    AxisData m_axisData;
};
//QML_DECLARE_TYPE(Alignment)
#endif // ALIGNMENT_H
