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
#include "audience.h"

Audience::Audience(QObject *parent) : QObject(parent), m_start(5, 1.8), m_stop(60, 1.8)
{
    connect(this, &Audience::startChanged, [this]() {
        emit changed();
    });
    connect(this, &Audience::stopChanged, [this]() {
        emit changed();
    });
}

QPointF &Audience::start() noexcept
{
    return m_start;
}

const QPointF &Audience::start() const noexcept
{
    return m_start;
}

void Audience::setStart(const QPointF &start) noexcept
{
    if (m_start != start) {
        m_start = start;
        emit startChanged(m_start);
    }
}

QPointF &Audience::stop() noexcept
{
    return m_stop;
}

const QPointF &Audience::stop() const noexcept
{
    return m_stop;
}

void Audience::setStop(const QPointF &stop) noexcept
{
    if (m_stop != stop) {
        m_stop = stop;
        emit stopChanged(m_stop);
    }
}
