#ifndef SENSOR_LIST_H
#define SENSOR_LIST_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include "Sensor.h"
#include "../BaseClass.h"

class SensorList : public BaseClass {
Q_OBJECT
    Q_PROPERTY(QList<Sensor *> list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit SensorList(QObject *parent = nullptr);

    ~SensorList() override {
        for (auto &s : this->sensorList)
            delete s;

        delete this->client;
    }

    void initialize();

    QList<Sensor *> getList();

    void setList(QList<Sensor *> list);

    void resetList();

    int count() const;

    void create(Sensor *sensor);

    void remove(Sensor *sensor);

    bool nameExists(const QString &val);

    QStringList nameList() const;

    void setDevice(const util::types::Device &val);

    util::types::DeviceType getDeviceType() const;

private:
    void getSensorsFromServer();

    void attach(Sensor *sensor, const util::types::Sensor &data);

    void detach(Sensor *sensor);

public slots:



signals:

    void sensorChanged();

    void listChanged();

    void beginInsert();

    void endInsert();

    void beginRemove(int index);

    void endRemove();

    void createFinish();

private:
    QList<Sensor *> sensorList;
    util::types::Device device;
};

#endif //SENSOR_LIST_H