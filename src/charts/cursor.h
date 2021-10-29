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
#ifndef CHARTCURSOR_H
#define CHARTCURSOR_H

#include <QQuickPaintedItem>
#include "padding.h"
#include "axis.h"

class ChartCursor : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    QML_ELEMENT

public:
    ChartCursor(const ChartPadding &padding, const ChartAxis &x, const ChartAxis &y, QQuickItem *parent = Q_NULLPTR);
    void paint(QPainter *painter) noexcept override;

    qreal x() const;
    void setX(qreal newX);

    qreal y() const;
    void setY(qreal newY);

public slots:
    void updateWidth();
    void updateHeight();

signals:
    void xChanged();
    void yChanged();

private:
    qreal m_x, m_y;
    const ChartPadding &m_padding;
    const ChartAxis &m_axisX, &m_axisY;
};

#endif // CHARTCURSOR_H
