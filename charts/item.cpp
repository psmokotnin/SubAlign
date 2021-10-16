#include "item.h"
#include <QPainter>
#include <QPainterPath>

ChartItem::ChartItem(QQuickItem *parent) : QQuickPaintedItem(parent),
    m_alignment(nullptr), m_x(ChartAxis::Horizontal, this), m_y(ChartAxis::Vertical, this), m_padding()
{
    setFlag(QQuickItem::ItemHasContents);
    m_x.setPadding(m_padding);
    m_y.setPadding(m_padding);
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

QRectF ChartItem::paddingRect() const noexcept
{
    return QRectF{
        m_padding.left,
        m_padding.bottom,
        width() - m_padding.left - m_padding.right,
        height() - m_padding.top - m_padding.bottom
    };
}
