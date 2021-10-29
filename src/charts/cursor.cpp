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
#include "cursor.h"
#include <QPainter>

ChartCursor::ChartCursor(const ChartPadding &padding, const ChartAxis &x, const ChartAxis &y,
                         QQuickItem *parent) : QQuickPaintedItem(parent),
    m_x(NAN), m_y(NAN), m_padding(padding), m_axisX(x), m_axisY(y)
{
    connect(parent, SIGNAL(widthChanged()), this, SLOT(updateWidth()));
    connect(parent, SIGNAL(heightChanged()), this, SLOT(updateHeight()));

    updateWidth();
    updateHeight();
}

void ChartCursor::updateWidth()
{
    setWidth(parentItem()->width());
}

void ChartCursor::updateHeight()
{
    setHeight(parentItem()->height());
}

void ChartCursor::paint(QPainter *painter) noexcept
{
    if (std::isnan(m_x) || std::isnan(m_x)) {
        return;
    }

    QPoint p1, p2;
    qreal t;

    QPen cursorPen(QColor("grey"), 1);
    painter->setPen(cursorPen);
    t = m_axisX.pwidth() * (x() - m_axisX.min()) / (m_axisX.max() - m_axisX.min());

    p1.setX(static_cast<int>(t + m_padding.left));
    p2.setX(static_cast<int>(t + m_padding.left));
    p1.setY(static_cast<int>(m_axisX.heightf() - m_padding.bottom));
    p2.setY(static_cast<int>(m_padding.top));
    painter->drawLine(p1, p2);

    t = m_axisY.pheight() * (y() - m_axisY.min()) / (m_axisY.max() - m_axisY.min());
    p1.setX(static_cast<int>(m_padding.left));
    p2.setX(static_cast<int>(m_axisY.widthf() - m_padding.right));
    p1.setY(static_cast<int>(m_axisY.heightf() - m_padding.bottom - t));
    p2.setY(static_cast<int>(m_axisY.heightf() - m_padding.bottom - t));
    painter->drawLine(p1, p2);
}

qreal ChartCursor::x() const
{
    return m_x;
}

void ChartCursor::setX(qreal newX)
{
    if (qFuzzyCompare(m_x, newX))
        return;
    m_x = newX;
    emit xChanged();
    update();
}

qreal ChartCursor::y() const
{
    return m_y;
}

void ChartCursor::setY(qreal newY)
{
    if (qFuzzyCompare(m_y, newY))
        return;
    m_y = newY;
    emit yChanged();
    update();
}
