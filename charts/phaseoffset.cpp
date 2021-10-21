#include "phaseoffset.h"
#include <QPainter>
#include <QPainterPath>

PhaseOffsetChart::PhaseOffsetChart(QQuickItem *parent) : ChartItem(parent)
{
}

void PhaseOffsetChart::paintChart(QPainter *painter)
{
    qreal lastPhase = NAN;
    QPen linePen(m_color, 2);
    QPainterPath path;
    QPoint xo;

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

        if (std::isnan(lastPhase)) {
            lastPhase = phase;
        }
        if (lastPhase * phase <= 0.1) {
            xo = point;
        }
        lastPhase = phase;
    }

    painter->setPen(linePen);
    painter->drawPath(path);

    if (!xo.isNull()) {
        painter->setBrush({"white"});
        painter->drawEllipse(xo, 10, 10);

        auto delta = std::hypot(10., 10.) / 2.;
        path.clear();
        path.moveTo(xo + QPoint(-delta, -delta));
        path.lineTo(xo + QPoint(delta, delta));
        path.moveTo(xo + QPoint(-delta, delta));
        path.lineTo(xo + QPoint(delta, -delta));
        painter->drawPath(path);
    }
    setXo(xo);
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

QPoint PhaseOffsetChart::xo() const
{
    return m_xo;
}

void PhaseOffsetChart::setXo(QPoint newXo)
{
    if (m_xo == newXo)
        return;
    m_xo = newXo;
    emit xoChanged();
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
