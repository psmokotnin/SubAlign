#ifndef CHARTAXIS_H
#define CHARTAXIS_H

#include <QQuickPaintedItem>
#include "padding.h"

class ChartAxis : public QQuickPaintedItem
{
    Q_OBJECT
public:
    enum Direction {Vertical, Horizontal};
    ChartAxis(Direction direction, QQuickItem *parent = Q_NULLPTR);

    void configure(float min, float max, unsigned int ticks = 0);
    void configure(unsigned int ticks = 0);
    void paint(QPainter *painter) noexcept override;
    QString format(float v);
    float convert(float value) const;

    float min() const;
    void setMin(float newMin);

    float max() const;
    void setMax(float newMax);

    Direction direction() const;
    void setDirection(Direction newDirection);

    const ChartPadding &padding() const;
    void setPadding(const ChartPadding &newPadding);

    float pwidth() const noexcept;
    float pheight() const noexcept;
    float widthf() const noexcept;
    float heightf() const noexcept;

public slots:
    void updateWidth();
    void updateHeight();

private:
    void generateLabels(unsigned int ticks);

    Direction m_direction;
    ChartPadding m_padding;
    float m_min, m_max, m_centralLabel;
    std::vector<float> m_labels;

};

#endif // CHARTAXIS_H
