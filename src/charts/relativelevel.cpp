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
#include "relativelevel.h"
#include <QImage>
#include <QPainter>

RelativeLevelChart::RelativeLevelChart(QQuickItem *parent) : ChartItem(parent), m_plane(XY)
{
    setFlag(QQuickItem::ItemHasContents);
    m_x.setUnit("m");
    m_y.setUnit("m");
    m_unit = "";
}
void RelativeLevelChart::paintChart(QPainter *painter)
{
    QImage image(innerWidth(), innerHeight(), QImage::Format_ARGB32);

    static std::vector<QColor> colors = {
        "#EB341C", //red
        "#FBFB54", //yellow
        "#357C24", //green
    };
    auto const &a = m_alignment->audience()->start();
    auto const &b = m_alignment->audience()->stop();
    auto k = (b.y() - a.y()) / (b.x() - a.x());
    auto c = a.y() - a.x() * k;

    for (auto imageX = 0; imageX < innerWidth(); ++imageX ) {
        for (auto imageY = 0; imageY < innerHeight(); ++imageY ) {

            auto x = m_x.reverse(imageX + m_padding.left);
            auto y = (m_plane == XY ? k * x + c : m_y.reverse(imageY + m_padding.top));
            auto z = (m_plane == XY ? m_y.reverse(imageY + m_padding.top) : 0);

            auto zone = m_alignment->zone(x, y, z);
            QColor color;
            switch (zone.first) {
            case Alignment::LevelZone::Combing:
                color = colors[0];
                break;
            case Alignment::LevelZone::Transition:
                color = colors[1];
                break;
            case Alignment::LevelZone::Isolation:
                color = colors[2];
                break;
                break;
            }

            if (zone.second == Alignment::PhaseZone::Coupling &&
                    (
                        (imageX % 8 >= 4 && imageY % 8 >= 4) ||
                        (imageX % 8 < 4 && imageY % 8 < 4)
                    )
               ) {
                color = QColor("black");
            }

            image.setPixelColor(imageX, imageY, color);
        }
    }

    painter->drawImage(paddingRect(), image);
}

void RelativeLevelChart::applyAlignment()
{
    if (m_alignment) {
        auto delta = m_alignment->audience()->stop().x() - m_alignment->audience()->start().x();
        m_x.configure(m_alignment->audience()->start().x(),
                      m_alignment->audience()->stop().x(),
                      10);
        switch (m_plane) {
        case XY:
            m_y.configure(-delta / 2, delta / 2, 9);
            break;
        case XZ:
            m_y.configure(0, delta, 9);
            break;
        }

        connect(m_alignment->audience(), &Audience::startChanged, [this]() {
            m_x.setMin(m_alignment->audience()->start().x());
            m_x.configure(10);
        });

        connect(m_alignment->audience(), &Audience::stopChanged, [this]() {
            m_x.setMax(m_alignment->audience()->stop().x());
            m_x.configure(10);
        });
    }
}

RelativeLevelChart::Plane RelativeLevelChart::plane() const noexcept
{
    return m_plane;
}

void RelativeLevelChart::setPlane(Plane newPlane) noexcept
{
    if (m_plane == newPlane)
        return;
    m_plane = newPlane;
    emit planeChanged();
}

QString RelativeLevelChart::value(QPoint position) const noexcept
{
    auto const &a = m_alignment->audience()->start();
    auto const &b = m_alignment->audience()->stop();
    auto k = (b.y() - a.y()) / (b.x() - a.x());
    auto c = a.y() - a.x() * k;

    auto x = m_x.reverse(position.x());
    auto y = (m_plane == XY ? k * x + c : m_y.reverse(position.y()));
    auto z = (m_plane == XY ? m_y.reverse(position.y()) : 0);
    auto zone = m_alignment->zone(x, y, z);

    QMetaEnum levelEnum = QMetaEnum::fromType<Alignment::LevelZone>();
    QMetaEnum phaseEnum = QMetaEnum::fromType<Alignment::PhaseZone>();

    return QString(levelEnum.valueToKey(zone.first)) + " "  + QString(phaseEnum.valueToKey(zone.second));
}
