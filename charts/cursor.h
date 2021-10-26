#ifndef CHARTCURSOR_H
#define CHARTCURSOR_H

#include <QQuickPaintedItem>
#include "padding.h"
#include "axis.h"

class ChartCursor : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    QML_ELEMENT

public:
    ChartCursor(const ChartPadding &padding, const ChartAxis &x, const ChartAxis &y, QQuickItem *parent = Q_NULLPTR);
    void paint(QPainter *painter) noexcept override;

    qreal x() const;
    void setX(qreal newX);

    qreal y() const;
    void setY(qreal newY);

public slots:
    void updateWidth();
    void updateHeight();

signals:
    void xChanged();
    void yChanged();

private:
    qreal m_x, m_y;
    const ChartPadding &m_padding;
    const ChartAxis &m_axisX, &m_axisY;
};

#endif // CHARTCURSOR_H
