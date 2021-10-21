#ifndef PHASEOFFSETCHART_H
#define PHASEOFFSETCHART_H

#include "item.h"

class PhaseOffsetChart : public ChartItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPoint xo READ xo WRITE setXo NOTIFY xoChanged)

public:
    PhaseOffsetChart(QQuickItem *parent = Q_NULLPTR);

    const QColor &color() const;
    void setColor(const QColor &newColor);

    QPoint xo() const;
    void setXo(QPoint newXo);

signals:
    void colorChanged();

    void xoChanged();

protected:
    void paintChart(QPainter *painter) override;
    virtual void applyAlignment() override;

private:
    QColor m_color;
    QPoint m_xo;
};

#endif // PHASEOFFSETCHART_H
