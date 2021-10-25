#ifndef PHASEOFFSETCHART_H
#define PHASEOFFSETCHART_H

#include "item.h"

class PhaseOffsetChart : public ChartItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal xo READ xo WRITE setXo NOTIFY xoChanged)

public:
    PhaseOffsetChart(QQuickItem *parent = Q_NULLPTR);

    const QColor &color() const;
    void setColor(const QColor &newColor);

    qreal xo() const;
    void setXo(qreal newXo);

    Q_INVOKABLE QString value(QPoint position) const noexcept override;

signals:
    void colorChanged();
    void xoChanged();

protected:
    void paintChart(QPainter *painter) override;
    virtual void applyAlignment() override;

private:
    QColor m_color;
    qreal m_xo;
};

#endif // PHASEOFFSETCHART_H
