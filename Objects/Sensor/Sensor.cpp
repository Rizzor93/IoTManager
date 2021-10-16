#include "Sensor.h"


Sensor::Sensor(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
}

void Sensor::initialize() {
    this->setSensor(this->client->GetSensor(this->sensor.ID));
}

void Sensor::update() {
    this->client->UpdateSensor(this->getSensor());
    this->changed();
}

void Sensor::remove() {
    this->client->DeleteSensor(this->sensor.ID);
    delete this;
}

int Sensor::getDeviceID() const {
    return this->sensor.DeviceID;
}

void Sensor::setDeviceID(const int &val) {
    this->sensor.DeviceID = val;
    emit this->deviceIDChanged();
}

int Sensor::getSensorID() const {
    return this->sensor.ID;
}

void Sensor::setSensorID(const int &val) {
    this->sensor.ID = val;
    emit this->sensorIDChanged();
}

QString Sensor::getName() const {
    return this->sensor.Name;
}

void Sensor::setName(const QString &val) {
    this->sensor.Name = val;
    emit this->nameChanged();
}

util::types::SensorDataType Sensor::getSensorDataType() const {
    return this->sensor.SensorDataType;
}

void Sensor::setSensorDataType(const util::types::SensorDataType &val) {
    this->sensor.SensorDataType = val;
    emit this->sensorDataTypeChanged();
}

util::types::PLCDataArea Sensor::getPlcDataArea() const {
    return this->sensor.PLCDataArea;
}

void Sensor::setPlcDataArea(const util::types::PLCDataArea &val) {
    this->sensor.PLCDataArea = val;
    emit this->plcDataAreaChanged();
}

int Sensor::getDataOffset() const {
    return this->sensor.DataOffset;
}

void Sensor::setDataOffset(const int &val) {
    this->sensor.DataOffset = val;
    emit this->dataOffsetChanged();
}

int Sensor::getBoolIndex() const {
    return this->sensor.BoolIndex;
}

void Sensor::setBoolIndex(const int &val) {
    this->sensor.BoolIndex = val;
    emit this->boolIndexChanged();
}

int Sensor::getDbNum() const {
    return this->sensor.DbNum;
}

void Sensor::setDbNum(const int &val) {
    this->sensor.DbNum = val;
    emit this->dbNumChanged();
}

QString Sensor::getNodeID() const {
    return this->sensor.NodeID;
}

void Sensor::setNodeID(const QString &val) {
    this->sensor.NodeID = val;
    emit this->nodeIDChanged();
}

int Sensor::getGPIONum() const {
    return this->sensor.GPIONum;
}

void Sensor::setGPIONum(const int &val) {
    this->sensor.GPIONum = val;
    emit this->gpioNumChanged();
}

util::types::GPIOType Sensor::getGPIOType() const {
    return this->sensor.GPIOType;
}

void Sensor::setGPIOType(const util::types::GPIOType &val) {
    this->sensor.GPIOType = val;
    emit this->gpioTypeChanged();
}

bool Sensor::getPullUpResistor() const {
    return this->sensor.PullUpResistor;
}

void Sensor::setPullUpResistor(const bool &val) {
    this->sensor.PullUpResistor = val;
    emit this->pullUpResistorChanged();
}

util::types::Sensor Sensor::getSensor() {
    return this->sensor;
}

void Sensor::setSensor(const util::types::Sensor &val) {
    this->sensor = val;
}

