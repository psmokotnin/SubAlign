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
