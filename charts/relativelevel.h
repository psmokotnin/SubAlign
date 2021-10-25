#ifndef RELATIVELEVELCHART_H
#define RELATIVELEVELCHART_H

#include "item.h"

class RelativeLevelChart : public ChartItem
{
public:
    enum Plane {XY, XZ};
    Q_OBJECT
    Q_PROPERTY(Plane plane READ plane WRITE setPlane NOTIFY planeChanged)
    QML_ELEMENT
    Q_ENUM(Plane)

public:
    RelativeLevelChart(QQuickItem *parent = Q_NULLPTR);

    RelativeLevelChart::Plane plane() const noexcept;
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

#endif // RELATIVELEVELCHART_H
