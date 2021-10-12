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

public:
    explicit Alignment(QObject *parent = nullptr);

    qreal maxPhaseOffset() const;
    void setMaxPhaseOffset(const qreal &maxPhaseOffset);

    qreal frequency() const;
    void setFrequency(const qreal &frequency);

    Environment *environment();
    Loudspeaker *subwoofer();
    Loudspeaker *mains();
    Audience *audience();

signals:
    void maxPhaseOffsetChanged(qreal);
    void frequencyChanged(qreal);

private:
    qreal m_maxPhaseOffset = 0;
    qreal m_frequency = 100;

    Environment m_environment;
    Loudspeaker m_subwoofer, m_mains;
    Audience m_audience;
};
//QML_DECLARE_TYPE(Alignment)
#endif // ALIGNMENT_H
