/**
 *  SubAlign
 *  Copyright (C) 2021  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
    struct DataPoint {
        struct {
            qreal mains;
            qreal subwoofer;
            qreal sum;
        } spl;
        qreal phase;
    };
    enum LevelZone {
        Combing         = 0b001,
        Transition      = 0b010, //in Bob's book it is Combining
        Isolation       = 0b100
    };
    enum PhaseZone {
        Coupling        = 0b01000,
        Cancellation    = 0b10000
    };
    Q_ENUM(LevelZone)
    Q_ENUM(PhaseZone)

    qreal yOnAxis(qreal x) const noexcept;

    qreal maxPhaseOffset() const noexcept;
    void setMaxPhaseOffset(const qreal &maxPhaseOffset);

    qreal frequency() const noexcept;
    void setFrequency(const qreal &frequency);

    Audience *audience() noexcept;
    Environment *environment() noexcept;
    Loudspeaker *mains() noexcept;
    Loudspeaker *subwoofer() noexcept;

    const AxisData &phase() const;
    DataPoint calculate(qreal x, qreal y, qreal z) const noexcept;
    std::pair<LevelZone, PhaseZone> zone(qreal x, qreal y, qreal z) const noexcept;

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

    qreal m_phaseOffset, m_levelOffset;

    Audience m_audience;
    Environment m_environment;
    Loudspeaker m_mains, m_subwoofer;

    AxisData m_axisData;
};
//QML_DECLARE_TYPE(Alignment)
#endif // ALIGNMENT_H
