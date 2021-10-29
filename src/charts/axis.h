#ifndef CHARTAXIS_H
#define CHARTAXIS_H

#include <QQuickPaintedItem>
#include "padding.h"

class ChartAxis : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString unit READ unit CONSTANT)
    QML_ELEMENT

public:
    enum Direction {Vertical, Horizontal};
    ChartAxis(Direction direction, const ChartPadding &newPadding, QQuickItem *parent = Q_NULLPTR);

    void configure(qreal min, qreal max, unsigned int ticks = 0);
    void configure(unsigned int ticks = 0);
    void paint(QPainter *painter) noexcept override;
    QString format(qreal v);
    qreal convert(qreal value) const;
    qreal reverse(qreal value) const;

    qreal min() const;
    void setMin(qreal newMin);

    qreal max() const;
    void setMax(qreal newMax);

    Direction direction() const;
    void setDirection(Direction newDirection);

    const ChartPadding &padding() const;

    qreal pwidth() const noexcept;
    qreal pheight() const noexcept;
    qreal widthf() const noexcept;
    qreal heightf() const noexcept;

    const QString &unit() const;
    void setUnit(QString unit) noexcept;

public slots:
    void updateWidth();
    void updateHeight();

private:
    void generateLabels(unsigned int ticks);

    Direction m_direction;
    const ChartPadding &m_padding;
    qreal m_min, m_max, m_centralLabel;
    std::vector<qreal> m_labels;
    QString m_unit;
};

#endif // CHARTAXIS_H
