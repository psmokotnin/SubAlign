#include "phaseoffset.h"
#include <QPainter>
#include <QPainterPath>

PhaseOffsetChart::PhaseOffsetChart(QQuickItem *parent) : ChartItem(parent)
{
    m_x.setUnit("m");
    m_y.setUnit("˚");
    m_unit = "˚";
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
        xo.setY(m_y.convert(0));

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
    setXo(m_x.reverse(xo.x()));
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

qreal PhaseOffsetChart::xo() const
{
    return m_xo;
}

void PhaseOffsetChart::setXo(qreal newXo)
{
    if (qFuzzyCompare(m_xo, newXo)) {
        return;
    }
    m_xo = newXo;
    emit xoChanged();
}

QString PhaseOffsetChart::value(QPoint position) const noexcept
{
    auto x = m_x.reverse(position.x());
    auto y = m_alignment->yOnAxis(x);
    auto dataPoint = m_alignment->calculate(x, y, 0);
    return QString::number(dataPoint.phase, 'f', 0);
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
