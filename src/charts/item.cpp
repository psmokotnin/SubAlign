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
#include "item.h"
#include <QPainter>
#include <QPainterPath>

ChartItem::ChartItem(QQuickItem *parent) : QQuickPaintedItem(parent),
    m_alignment(nullptr),
    m_x(ChartAxis::Horizontal, m_padding, this),
    m_y(ChartAxis::Vertical, m_padding, this),
    m_padding(), m_cursor(m_padding, m_x, m_y, this),
    m_unit()
{
    setFlag(QQuickItem::ItemHasContents);
    setZ(z() + 1);
}

void ChartItem::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

    QPainterPath clip;
    auto frame = paddingRect();
    clip.moveTo(frame.left(), frame.top());
    clip.lineTo(frame.right(), frame.top());
    clip.lineTo(frame.right(), frame.bottom());
    clip.lineTo(frame.left(), frame.bottom());
    clip.closeSubpath();
    painter->setClipPath(clip);

    paintChart(painter);
}

Alignment *ChartItem::alignment() const
{
    return m_alignment;
}

void ChartItem::setAlignment(Alignment *newAlignment)
{
    if (m_alignment == newAlignment)
        return;

    m_alignment = newAlignment;
    connect(m_alignment, &Alignment::ready, [this] () {
        update();
    });
    emit alignmentChanged();
    applyAlignment();
    update();
}

qreal ChartItem::innerWidth() const noexcept
{
    return width() - m_padding.left - m_padding.right;
}

qreal ChartItem::innerHeight() const noexcept
{
    return height() - m_padding.top - m_padding.bottom;
}

QRectF ChartItem::paddingRect() const noexcept
{
    return QRectF{
        m_padding.left,
        m_padding.bottom,
        innerWidth(),
        innerHeight()
    };
}

QPointF ChartItem::point(QPoint position) const noexcept
{
    auto rect = paddingRect();
    if (!rect.contains(position)) {
        return {NAN, NAN};
    }
    return {
        m_x.reverse(position.x()),
        m_y.reverse(position.y()),
    };
}

QString ChartItem::value(QPoint position) const noexcept
{
    Q_UNUSED(position);
    return {};
}

ChartAxis *ChartItem::x() noexcept
{
    return &m_x;
}

ChartAxis *ChartItem::y() noexcept
{
    return &m_y;
}

ChartCursor *ChartItem::cursor() noexcept
{
    return &m_cursor;
}

const QString &ChartItem::unit() const
{
    return m_unit;
}
