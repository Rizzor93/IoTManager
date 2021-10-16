#include "SensorList.h"

#include <utility>

SensorList::SensorList(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
}

void SensorList::initialize() {
    this->getSensorsFromServer();
}

void SensorList::getSensorsFromServer() {
    QList<util::types::Sensor> tmp = this->client->GetSensors(this->device.ID);

    for (auto &s : this->sensorList)
        this->detach(s);

    for (auto const &s : tmp)
        this->attach(new Sensor(), s);

}

QList<Sensor *> SensorList::getList() {
    return this->sensorList;
}

void SensorList::setList(QList<Sensor *> list) {
    this->sensorList = std::move(list);
    emit this->listChanged();
}

void SensorList::resetList() {
    qDeleteAll(this->sensorList.begin(), this->sensorList.end());
    this->sensorList.clear();
}

int SensorList::count() const {
    return this->sensorList.count();
}

void SensorList::create(Sensor *sensor) {
    this->client->CreateSensor(sensor->getSensor());

    this->getSensorsFromServer();
}

void SensorList::remove(Sensor *sensor) {
    if (!this->sensorList.empty()) {

        emit this->beginRemove(this->sensorList.indexOf(sensor));
        this->sensorList.removeOne(sensor);
        sensor->remove();

        emit this->endRemove();
    }

    emit this->listChanged();
}

bool SensorList::nameExists(const QString &val) {
    for (auto const &r : this->sensorList) {
        if (r->getName() == val)
            return true;
    }
    return false;
}

QStringList SensorList::nameList() const {
    QStringList nameList;

    for (auto const &sensor : this->sensorList)
        nameList << sensor->getName();

    return nameList;
}

void SensorList::attach(Sensor *sensor, const util::types::Sensor &data) {
    emit this->beginInsert();

    sensor->setSensor(data);
    connect(sensor, &Sensor::changed, this, &SensorList::sensorChanged);

    this->sensorList.push_back(sensor);

    emit this->endInsert();
}

void SensorList::detach(Sensor *sensor) {
    emit this->beginRemove(this->sensorList.indexOf(sensor));

    this->sensorList.removeOne(sensor);
    delete sensor;

    emit this->endRemove();
}

void SensorList::setDevice(const util::types::Device &val) {
    this->device = val;
}

util::types::DeviceType SensorList::getDeviceType() const {
    return this->device.DeviceType;
}








