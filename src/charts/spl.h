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
