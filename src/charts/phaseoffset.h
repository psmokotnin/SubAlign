/**
 *  SubAlign
 *  Copyright (C) 2021  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
