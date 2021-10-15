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

    qreal x() const;
    void setX(const qreal &x);

    qreal y() const;
    void setY(const qreal &y);

    qreal level() const;
    void setLevel(const qreal &level);

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
