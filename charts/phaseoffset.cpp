#include "phaseoffset.h"
#include <QPainter>
#include <QPainterPath>

PhaseOffsetChart::PhaseOffsetChart(QQuickItem *parent) : ChartItem(parent)
{
}

void PhaseOffsetChart::paintChart(QPainter *painter)
{
    QPen linePen(m_color, 2);
    QPainterPath path;

    for (auto &&[x, phase, spl] : m_alignment->phase()) {
        auto point = QPoint(
                         m_x.convert(x),
                         m_y.convert(phase)
                     );
        if (path.elementCount()) {
            path.lineTo(point);
        } else {
            path.moveTo(point);
        }
    }

    painter->setPen(linePen);
    painter->drawPath(path);
}

void PhaseOffsetChart::applyAlignment()
{
    if (m_alignment) {
        m_x.configure(m_alignment->audience()->start().x(),
                      m_alignment->audience()->stop().x(),
                      10);
        m_y.configure(-180, 180, 9);

        connect(m_alignment->audience(), &Audience::startChanged, [this]() {
            m_x.setMin(m_alignment->audience()->start().x());
            m_x.configure(10);
        });

        connect(m_alignment->audience(), &Audience::stopChanged, [this]() {
            m_x.setMax(m_alignment->audience()->stop().x());
            m_x.configure(10);
        });
    }
}

const QColor &PhaseOffsetChart::color() const
{
    return m_color;
}

void PhaseOffsetChart::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}
