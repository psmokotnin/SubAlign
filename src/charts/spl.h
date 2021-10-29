#ifndef SPL_H
#define SPL_H

#include "item.h"

class SplChart : public ChartItem
{
    Q_OBJECT
    Q_PROPERTY(QColor mainsColor READ mainsColor WRITE setMainsColor NOTIFY mainsColorChanged)
    Q_PROPERTY(QColor subwooferColor READ subwooferColor WRITE setSubwooferColor NOTIFY subwooferColorChanged)
    Q_PROPERTY(QColor sumColor READ sumColor WRITE setSumColor NOTIFY sumColorChanged)
    QML_ELEMENT

public:
    SplChart(QQuickItem *parent = Q_NULLPTR);

    const QColor &sumColor() const;
    void setSumColor(const QColor &newSumColor);

    const QColor &subwooferColor() const;
    void setSubwooferColor(const QColor &newSubwooferColor);

    const QColor &mainsColor() const;
    void setMainsColor(const QColor &newMainsColor);

    Q_INVOKABLE QString value(QPoint position) const noexcept override;

signals:
    void sumColorChanged();
    void subwooferColorChanged();
    void mainsColorChanged();

protected:
    void paintChart(QPainter *painter) override;
    virtual void applyAlignment() override;

private:
    QColor m_mainsColor;
    QColor m_subwooferColor;
    QColor m_sumColor;
};

#endif // SPL_H
