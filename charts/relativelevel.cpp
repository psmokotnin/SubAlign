#include "relativelevel.h"
#include <QImage>
#include <QPainter>

RelativeLevelChart::RelativeLevelChart(QQuickItem *parent) : ChartItem(parent), m_plane(XY)
{
    setFlag(QQuickItem::ItemHasContents);
}
void RelativeLevelChart::paintChart(QPainter *painter)
{
    QImage image(innerWidth(), innerHeight(), QImage::Format_ARGB32);

    static std::vector<QColor> colors = {
        "#EB341C", //red
        "#FBFB54", //yellow
        "#357C24", //green

        "#CCEB341C", //red
        "#CCFBFB54", //yellow
        "#CC357C24", //green
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
            case Alignment::LevelZone::Combining:
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
