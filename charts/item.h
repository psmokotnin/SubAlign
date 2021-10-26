#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QQuickPaintedItem>
#include "axis.h"
#include "alignment.h"
#include "cursor.h"

class ChartItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Alignment *alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(ChartAxis *x READ x CONSTANT)
    Q_PROPERTY(ChartAxis *y READ y CONSTANT)
    Q_PROPERTY(ChartCursor *cursor READ cursor CONSTANT)
    Q_PROPERTY(QString unit READ unit CONSTANT)

public:
    ChartItem(QQuickItem *parent = Q_NULLPTR);
    virtual void paint(QPainter *painter) override;

    Alignment *alignment() const;
    void setAlignment(Alignment *newAlignment);

    qreal innerWidth() const noexcept;
    qreal innerHeight() const noexcept;
    QRectF paddingRect() const noexcept;

    Q_INVOKABLE QPointF point(QPoint position) const noexcept;
    Q_INVOKABLE virtual QString value(QPoint position) const noexcept;

    ChartAxis *x() noexcept;
    ChartAxis *y() noexcept;

    ChartCursor *cursor() noexcept;

    const QString &unit() const;

signals:
    void alignmentChanged();

protected:
    virtual void paintChart(QPainter *painter) = 0;
    virtual void applyAlignment() = 0;

    Alignment *m_alignment;
    ChartAxis m_x, m_y;
    ChartPadding m_padding;
    ChartCursor m_cursor;
    QString m_unit;
};

#endif // CHARTITEM_H
