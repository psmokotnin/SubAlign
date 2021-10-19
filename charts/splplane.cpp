#include "splplane.h"
#include <QImage>
#include <QPainter>

SplPlaneChart::SplPlaneChart(QQuickItem *parent) : ChartItem(parent), m_plane(XY)
{
    setFlag(QQuickItem::ItemHasContents);
    //m_padding.right = 50;
}

void SplPlaneChart::paintChart(QPainter *painter)
{
    QImage image(innerWidth(), innerHeight(), QImage::Format_ARGB32);

    static std::vector<QColor> colors = {
        "#982018",  //0
        "#E83626",  //3
        "#E96233",  //6
        "#F2AB4B",  //9
        "#FFFD6A",  //12
        "#DDFB68",  //15
        "#A4FA72",  //18
        "#82FAAF",  //21
        "#78FBFD",  //24
        "#357BEC",  //27
        "#0634E8",  //30
        "#001FE6",  //33
        "#0016B5",  //36
        "#000867"   //39

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

            auto db = m_alignment->calculateSPL(x, y, z);
            auto index = std::floor(-db / 3.);
            if (index < 0) {
                index = 0;
            }
            if (index >= colors.size()) {
                index = colors.size() - 1;
            }

            image.setPixelColor(imageX, imageY, colors[index]);
        }
    }

    painter->drawImage(paddingRect(), image);
}

void SplPlaneChart::applyAlignment()
{
    if (m_alignment) {
        m_x.configure(m_alignment->audience()->start().x(),
                      m_alignment->audience()->stop().x(),
                      10);
        switch (m_plane) {
        case XY:
            m_y.configure(-30, 30, 9);
            break;
        case XZ:
            m_y.configure(0, 30, 9);
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

SplPlaneChart::Plane SplPlaneChart::plane() const noexcept
{
    return m_plane;
}

void SplPlaneChart::setPlane(Plane newPlane) noexcept
{
    if (m_plane == newPlane)
        return;
    m_plane = newPlane;
    emit planeChanged();
}
