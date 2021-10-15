#include "axis.h"
#include <QPainter>

ChartAxis::ChartAxis(Direction direction, QQuickItem *parent) : QQuickPaintedItem(parent),
    m_direction(direction), m_min(0), m_max(0), m_centralLabel(0), m_labels()
{
    connect(parent, SIGNAL(widthChanged()), this, SLOT(updateWidth()));
    connect(parent, SIGNAL(heightChanged()), this, SLOT(updateHeight()));

    updateWidth();
    updateHeight();
    setZ(-1);
}

void ChartAxis::updateWidth()
{
    setWidth(parentItem()->width());
}

void ChartAxis::updateHeight()
{
    setHeight(parentItem()->height());
}

void ChartAxis::configure(float min, float max, unsigned int ticks)
{
    setMin(min);
    setMax(max);
    generateLabels(ticks);
    update();
}

void ChartAxis::configure(unsigned int ticks)
{
    generateLabels(ticks);
    update();
}

void ChartAxis::paint(QPainter *painter) noexcept
{
    QPen linePen(QColor("grey"), 1);
    QPen centerLinePen(QColor("black"), 1);
    QPen textPen(QColor("grey"), 2);

    painter->setRenderHints(QPainter::Antialiasing, true);

    QPoint p1, p2;
    QRect textRect(0, 0, 50, 20), lastTextRect;
    float t;
    float size = (m_direction == Horizontal ? pwidth() : pheight());
    int alignFlag = static_cast<int>(m_direction == Horizontal ?
                                     Qt::AlignTop | Qt::AlignCenter :
                                     Qt::AlignRight | Qt::AlignHCenter
                                    );

    QRect limit(
        static_cast<int>(m_padding.left),
        static_cast<int>(m_padding.top),
        static_cast<int>(widthf()  - m_padding.left - m_padding.right ) + 1,
        static_cast<int>(heightf() - m_padding.top  - m_padding.bottom) + 1
    );
    auto setPoints = [&](float value) {
        t = size * (value - m_min) / (m_max - m_min);

        p1.setX(static_cast<int>(m_direction == Horizontal ? t + m_padding.left : m_padding.left));
        p2.setX(static_cast<int>(m_direction == Horizontal ? t + m_padding.left : widthf() - m_padding.right));

        p1.setY(static_cast<int>(m_direction == Horizontal ? heightf() - m_padding.bottom : heightf() -
                                 m_padding.bottom - t));
        p2.setY(static_cast<int>(m_direction == Horizontal ? m_padding.top : heightf() - m_padding.bottom - t));
    };
    for_each(m_labels.begin(), m_labels.end(), [&](float & l) {

        setPoints(l);
        //do not draw lines out of padding
        if (!limit.contains(p1) || !limit.contains(p2) )
            return;

        if (qFuzzyCompare(m_centralLabel, l)) {
            painter->setPen(centerLinePen);
        } else {
            painter->setPen(linePen);
        }
        painter->drawLine(p1, p2);

        painter->setPen(textPen);
        textRect.moveTo(
            p1.x() - (m_direction == Horizontal ? textRect.width() / 2 : textRect.width() + 5),
            p1.y() - (m_direction == Horizontal ? 0 : textRect.height() / 2)
        );

        //don't draw next label if it intersects lastone
        if (lastTextRect.isEmpty() || !lastTextRect.intersects(textRect)) {
            painter->drawText(textRect, alignFlag, format(l * scale()));
            lastTextRect = textRect;
        }
    });
}

QString ChartAxis::format(float v)
{
    bool addK = false;
    if (v >= 1000.f) {
        v /= 1000.f;
        addK = true;
    }
    v = std::round(v * 10.f) / 10.f;
    return QString::number(static_cast<double>(v)) + (addK ? "K" : "");
}

float ChartAxis::convert(float value) const
{
    auto scaled = (value - m_min) / (m_max - m_min);

    if (m_direction == Horizontal) {
        return pwidth() * scaled + padding().left;
    }
    return height() - (pheight() * scaled + padding().bottom);
}

float ChartAxis::min() const
{
    return m_min;
}

void ChartAxis::setMin(float newMin)
{
    m_min = newMin;
    update();
}

float ChartAxis::max() const
{
    return m_max;
}

void ChartAxis::setMax(float newMax)
{
    m_max = newMax;
    update();
}

ChartAxis::Direction ChartAxis::direction() const
{
    return m_direction;
}

void ChartAxis::setDirection(Direction newDirection)
{
    m_direction = newDirection;
    update();
}

void ChartAxis::generateLabels(unsigned int ticks)
{
    m_labels.clear();
    float l, step;

    //make symetrical labels if _min and _max have different signs
    if (std::abs(m_min + m_max) < std::max(abs(m_min), std::abs(m_max))) {
        l = 0;
        m_labels.push_back(l);
        ticks --;
        step = 2 * std::max(std::abs(m_min), std::abs(m_max)) / ticks;
        for (unsigned int i = 0; i < ticks / 2; i++) {
            l += step;
            m_labels.push_back(l);
            m_labels.push_back(-1 * l);
        }
    } else {
        l = m_min;
        step = std::abs(m_max - m_min) / ticks;
        for (unsigned int i = 0; i <= ticks; i++) {
            m_labels.push_back(l);
            l += step;
        }
    }
}

const ChartPadding &ChartAxis::padding() const
{
    return m_padding;
}

void ChartAxis::setPadding(const ChartPadding &newPadding)
{
    m_padding = newPadding;
}

float ChartAxis::pwidth() const noexcept
{
    return widthf()  - (m_padding.left + m_padding.right);
}

float ChartAxis::pheight() const noexcept
{
    return heightf() - (m_padding.top  + m_padding.bottom);
}

float ChartAxis::widthf() const noexcept
{
    return static_cast<float>(width());
}

float ChartAxis::heightf() const noexcept
{
    return static_cast<float>(height());
}
