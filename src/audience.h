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
#ifndef AUDIENCE_H
#define AUDIENCE_H

#include <QtQml>

class Audience : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QPointF stop READ stop WRITE setStop NOTIFY stopChanged)

public:
    explicit Audience(QObject *parent = nullptr);

    QPointF &start() noexcept;
    QPointF const &start() const noexcept;
    void setStart(const QPointF &start) noexcept;

    QPointF &stop() noexcept;
    QPointF const &stop() const noexcept;
    void setStop(const QPointF &stop) noexcept;

signals:
    void startChanged(const QPointF &);
    void stopChanged(const QPointF &);
    void changed();

private:
    QPointF m_start, m_stop;
};

#endif // AUDIENCE_H
