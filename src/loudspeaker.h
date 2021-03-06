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
#ifndef LOUDSPEAKER_H
#define LOUDSPEAKER_H

#include <QtQml>

class Loudspeaker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(qreal dB READ dB WRITE setDb NOTIFY levelChanged)
    QML_ELEMENT

public:
    explicit Loudspeaker(qreal x = 0, qreal y = 0, QObject *parent = nullptr);

    qreal x() const noexcept;
    void setX(const qreal &x) noexcept;

    qreal y() const noexcept;
    void setY(const qreal &y) noexcept;

    constexpr qreal z() const noexcept
    {
        return 0.;
    }

    qreal level() const noexcept;
    void setLevel(const qreal &level) noexcept;

    qreal dB() const;
    void setDb(qreal &value);

signals:
    void xChanged(qreal);
    void yChanged(qreal);
    void levelChanged(qreal);
    void changed();

private:
    qreal m_x = 0,
          m_y = 0,
          m_level = 1;

};

#endif // LOUDSPEAKER_H
