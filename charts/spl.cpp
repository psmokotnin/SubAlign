#include "spl.h"
#include <QPen>
#include <QPainter>

SplChart::SplChart(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

void SplChart::paint(QPainter *painter)
{
    QPen linePen(QColor("red"), 1);

    painter->setRenderHints(QPainter::Antialiasing, true);

    static const QPointF points[4] = {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0),
        QPointF(90.0, 70.0)
    };

    painter->drawConvexPolygon(points, 4);

}

