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

    QPointF start() const;
    void setStart(const QPointF &start);

    QPointF stop() const;
    void setStop(const QPointF &stop);

signals:
    void startChanged(const QPointF &);
    void stopChanged(const QPointF &);

private:
    QPointF m_start, m_stop;
};

#endif // AUDIENCE_H
