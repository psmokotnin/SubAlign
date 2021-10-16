#include "spl.h"
#include <QPainter>
#include <QPainterPath>

SplChart::SplChart(QQuickItem *parent) : ChartItem(parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

void SplChart::paintChart(QPainter *painter)
{
    QPen mainsPen(m_mainsColor, 2);
    QPen subwooferPen(m_subwooferColor, 2);
    QPen sumPen(m_sumColor, 2);
    QPainterPath mains, subwoofer, sum;

    for (auto &&[x, phase, spl] : m_alignment->phase()) {
        auto xPos = m_x.convert(x);
        auto pointMains = QPoint(xPos, m_y.convert(spl.mains));
        auto pointSub   = QPoint(xPos, m_y.convert(spl.subwoofer));
        auto pointSum   = QPoint(xPos, m_y.convert(spl.sum));

        if (mains.elementCount()) {
            mains.lineTo(pointMains);
            subwoofer.lineTo(pointSub);
            sum.lineTo(pointSum);
        } else {
            mains.moveTo(pointMains);
            subwoofer.moveTo(pointSub);
            sum.moveTo(pointSum);
        }
    }

    painter->setPen(mainsPen);
    painter->drawPath(mains);

    painter->setPen(subwooferPen);
    painter->drawPath(subwoofer);

    painter->setPen(sumPen);
    painter->drawPath(sum);
}

void SplChart::applyAlignment()
{
    if (m_alignment) {
        m_x.configure(m_alignment->audience()->start().x(),
                      m_alignment->audience()->stop().x(),
                      10);
        m_y.configure(-42, 6, 9);

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

const QColor &SplChart::mainsColor() const
{
    return m_mainsColor;
}

void SplChart::setMainsColor(const QColor &newMainsColor)
{
    if (m_mainsColor == newMainsColor)
        return;
    m_mainsColor = newMainsColor;
    emit mainsColorChanged();
}

const QColor &SplChart::subwooferColor() const
{
    return m_subwooferColor;
}

void SplChart::setSubwooferColor(const QColor &newSubwooferColor)
{
    if (m_subwooferColor == newSubwooferColor)
        return;
    m_subwooferColor = newSubwooferColor;
    emit subwooferColorChanged();
}

const QColor &SplChart::sumColor() const
{
    return m_sumColor;
}

void SplChart::setSumColor(const QColor &newSumColor)
{
    if (m_sumColor == newSumColor)
        return;
    m_sumColor = newSumColor;
    emit sumColorChanged();
}

