#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QQuickPaintedItem>
#include "axis.h"
#include "alignment.h"

class ChartItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Alignment *alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

public:
    ChartItem(QQuickItem *parent = Q_NULLPTR);
    virtual void paint(QPainter *painter) override;

    Alignment *alignment() const;
    void setAlignment(Alignment *newAlignment);

    QRectF paddingRect() const noexcept;

signals:
    void alignmentChanged();

protected:
    virtual void paintChart(QPainter *painter) = 0;
    virtual void applyAlignment() = 0;

    Alignment *m_alignment;
    ChartAxis m_x, m_y;
    ChartPadding m_padding;
};

#endif // CHARTITEM_H
