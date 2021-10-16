#include "RecordSensorList.h"

RecordSensorList::RecordSensorList(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
}

void RecordSensorList::initialize() {
    this->getSensorsFromServer();
}

void RecordSensorList::getSensorsFromServer() {
    QList<util::types::RecordSensor> tmp = this->client->GetRecord(this->record.ID).RecordSensor;

    for (auto &s : this->recordSensorList)
        this->detach(s);

    for (auto const &s : tmp)
        this->attach(new RecordSensor(), s);

}

QList<RecordSensor *> RecordSensorList::getList() const {
    return this->recordSensorList;
}

void RecordSensorList::setList(QList<RecordSensor *> list) {
    this->recordSensorList = std::move(list);
    emit this->listChanged();
}

void RecordSensorList::resetList() {
    qDeleteAll(this->recordSensorList.begin(), this->recordSensorList.end());
    this->recordSensorList.clear();
}

int RecordSensorList::count() const {
    return this->recordSensorList.count();
}

void RecordSensorList::create(RecordSensor *sensor) {
    auto tmp = new RecordSensor();
    tmp->setRecordSensor(sensor->getRecordSensor());
    this->attach(tmp, tmp->getRecordSensor());

    emit this->listChanged();
}

void RecordSensorList::remove(RecordSensor *sensor) {
    if (!this->recordSensorList.empty()) {

        emit this->beginRemove(this->recordSensorList.indexOf(sensor));
        this->recordSensorList.removeOne(sensor);
        delete sensor;

        emit this->endRemove();
    }

    emit this->listChanged();
}

void RecordSensorList::attach(RecordSensor *sensor, const util::types::RecordSensor &data) {
    emit this->beginInsert();

    sensor->setRecordSensor(data);
    sensor->setRecordID(this->record.ID);
    sensor->initialize();

    this->recordSensorList.push_back(sensor);

    emit this->endInsert();
}

void RecordSensorList::detach(RecordSensor *sensor) {
    emit this->beginRemove(this->recordSensorList.indexOf(sensor));

    this->recordSensorList.removeOne(sensor);
    delete sensor;

    emit this->endRemove();
}

util::types::Record RecordSensorList::getRecord() {
    return this->record;
}

void RecordSensorList::setRecord(const util::types::Record &val) {
    this->record = val;
}

QList<util::types::RecordSensor> RecordSensorList::getRecordSensor() const {
    QList<util::types::RecordSensor> tmp;

    for (auto const &s : this->recordSensorList)
        tmp << s->getRecordSensor();

    return tmp;
}
