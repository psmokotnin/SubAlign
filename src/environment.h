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
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QtQml>

class Environment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(qreal speedOfSound READ speedOfSound NOTIFY temperatureChanged)
    QML_ELEMENT

public:
    explicit Environment(QObject *parent = nullptr);

    qreal temperature() const;
    void setTemperature(const qreal &temperature);

    qreal speedOfSound() const noexcept;

signals:
    void temperatureChanged(qreal);
    void changed();

private:
    qreal m_temperature = 20.0;

};

#endif // ENVIRONMENT_H
