#include "item.h"
#include <QPainter>
#include <QPainterPath>

ChartItem::ChartItem(QQuickItem *parent) : QQuickPaintedItem(parent),
    m_alignment(nullptr), m_x(ChartAxis::Horizontal, m_padding, this), m_y(ChartAxis::Vertical, m_padding, this),
    m_padding()
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
