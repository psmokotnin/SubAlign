#ifndef PHASEOFFSETCHART_H
#define PHASEOFFSETCHART_H

#include "item.h"

class PhaseOffsetChart : public ChartItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    PhaseOffsetChart(QQuickItem *parent = Q_NULLPTR);

    const QColor &color() const;
    void setColor(const QColor &newColor);

signals:
    void colorChanged();

protected:
    void paintChart(QPainter *painter) override;
    virtual void applyAlignment() override;

private:
    QColor m_color;
};

#endif // PHASEOFFSETCHART_H
