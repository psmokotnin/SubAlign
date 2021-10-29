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
#include "spl.h"
#include <QPainter>
#include <QPainterPath>

SplChart::SplChart(QQuickItem *parent) : ChartItem(parent)
{
    setFlag(QQuickItem::ItemHasContents);
    m_x.setUnit("m");
    m_y.setUnit("dB");
    m_unit = "dB";
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

QString SplChart::value(QPoint position) const noexcept
{
    auto x = m_x.reverse(position.x());
    auto y = m_alignment->yOnAxis(x);
    auto dataPoint = m_alignment->calculate(x, y, 0);
    return QString::number(dataPoint.spl.sum, 'f', 1);
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

