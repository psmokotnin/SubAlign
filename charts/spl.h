#ifndef SPL_H
#define SPL_H

#include <QtQuick/QQuickPaintedItem>

class SplChart : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    SplChart(QQuickItem *parent = Q_NULLPTR);
    void paint(QPainter *painter);

signals:

};

#endif // SPL_H
