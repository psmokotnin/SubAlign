#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QtQml>

class Environment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(qreal speedOfSound READ speedOfSound NOTIFY temperatureChanged)
    QML_ELEMENT

public:
    explicit Environment(QObject *parent = nullptr);

    qreal temperature() const;
    void setTemperature(const qreal &temperature);

    qreal speedOfSound() const noexcept;

signals:
    void temperatureChanged(qreal);
    void changed();

private:
    qreal m_temperature = 20.0;

};

#endif // ENVIRONMENT_H
