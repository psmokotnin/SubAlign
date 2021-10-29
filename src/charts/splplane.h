#ifndef SPLPLANECHART_H
#define SPLPLANECHART_H

#include "item.h"

class SplPlaneChart : public ChartItem
{
public:
    enum Plane {XY, XZ};

    Q_OBJECT
    Q_PROPERTY(Plane plane READ plane WRITE setPlane NOTIFY planeChanged)
    QML_ELEMENT
    Q_ENUM(Plane)

public:
    SplPlaneChart(QQuickItem *parent = Q_NULLPTR);

    SplPlaneChart::Plane plane() const noexcept;
    void setPlane(Plane newPlane) noexcept;

    Q_INVOKABLE QString value(QPoint position) const noexcept override;

signals:
    void planeChanged();

protected:
    void paintChart(QPainter *painter) override;
    virtual void applyAlignment() override;

private:
    Plane m_plane;
};

#endif // SPLPLANECHART_H
