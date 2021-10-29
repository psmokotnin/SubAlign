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
#include "loudspeaker.h"

Loudspeaker::Loudspeaker(qreal x, qreal y, QObject *parent) : QObject(parent), m_x(x), m_y(y)
{
    connect(this, &Loudspeaker::xChanged, [this]() {
        emit changed();
    });
    connect(this, &Loudspeaker::yChanged, [this]() {
        emit changed();
    });
    connect(this, &Loudspeaker::levelChanged, [this]() {
        emit changed();
    });
}

qreal Loudspeaker::x() const noexcept
{
    return m_x;
}

void Loudspeaker::setX(const qreal &x) noexcept
{
    if (!qFuzzyCompare(m_x, x)) {
        m_x = x;
        emit xChanged(m_x);
    }
}

qreal Loudspeaker::y() const noexcept
{
    return m_y;
}

void Loudspeaker::setY(const qreal &y) noexcept
{
    if (!qFuzzyCompare(m_y, y)) {
        m_y = y;
        emit yChanged(m_y);
    }
}

qreal Loudspeaker::level() const noexcept
{
    return m_level;
}

void Loudspeaker::setLevel(const qreal &level) noexcept
{
    if (!qFuzzyCompare(m_level, level)) {
        m_level = level;
        emit levelChanged(m_level);
    }
}

qreal Loudspeaker::dB() const
{
    return 20.0 * std::log10(m_level);
}

void Loudspeaker::setDb(qreal &value)
{
    setLevel(std::pow(10, value / 20.0));
}
