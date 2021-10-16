#include "Record.h"

Record::Record(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
    this->recordSensorList = new RecordSensorList(this);
    connect(this->recordSensorList, &RecordSensorList::listChanged, this, &Record::update);
}

void Record::initialize() {
    this->setRecord(this->client->GetRecord(this->record.ID));

    this->recordSensorList->setRecord(this->getRecord());
    this->recordSensorList->initialize();
}

void Record::update() {
    this->client->UpdateRecord(this->getRecord());
    emit this->changed();
}

void Record::remove() {
    this->client->DeleteRecord(this->record.ID);
    delete this;
}

int Record::getRecordID() const {
    return this->record.ID;
}

void Record::setRecordID(const int &val) {
    this->record.ID = val;
    emit this->recordIDChanged();
}

int Record::getDeviceID() const {
    return this->record.DeviceID;
}

void Record::setDeviceID(const int &val) {
    this->record.DeviceID = val;
    emit this->deviceIDChanged();
}

QString Record::getName() const {
    return this->record.Name;
}

void Record::setName(const QString &val) {
    this->record.Name = val;
    emit this->nameChanged();
}

bool Record::getRunning() const {
    return this->record.Running;
}

void Record::setRunning(const bool &val) {
    this->record.Running = val;
    emit this->runningChanged();
}

util::types::Record Record::getRecord() {
    this->record.RecordSensor = this->recordSensorList->getRecordSensor();
    return this->record;
}

void Record::setRecord(const util::types::Record &val) {
    this->record = val;
}

