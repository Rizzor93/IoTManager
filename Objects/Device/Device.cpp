#include "Device.h"

Device::Device(QObject *parent){
    this->setParent(parent);
    this->connectGRPC();

    this->sensorList = new SensorList(this);
    this->recordList = new RecordList(this);
    connect(this->sensorList, &SensorList::sensorChanged, this->recordList, &RecordList::update);
    connect(this->sensorList, &SensorList::listChanged, this->recordList, &RecordList::update);
}

void Device::initialize() {
    this->setDevice(this->client->GetDevice(this->device.ID));

    this->sensorList->setDevice(this->getDevice());
    this->sensorList->initialize();

    this->recordList->setDevice(this->getDevice());
    this->recordList->initialize();

}

void Device::update() {
    this->client->UpdateDevice(this->getDevice());
}

void Device::remove() {
    this->client->DeleteDevice(this->device.ID);
    delete this;
}

int Device::getDeviceID() const {
    return this->device.ID;
}

void Device::setDeviceID(const int &val) {
    this->device.ID = val;
    emit this->deviceIDChanged();
}

QString Device::getName() const {
    return this->device.Name;
}

void Device::setName(const QString &val) {
    this->device.Name = val;
    emit this->nameChanged();
}

QString Device::getLocation() const {
    return this->device.Location;

}

void Device::setLocation(const QString &val) {
    this->device.Location = val;
    emit this->locationChanged();
}

util::types::DeviceType Device::getDeviceType() const {
    return this->device.DeviceType;
}

void Device::setDeviceType(const util::types::DeviceType &val) {
    this->device.DeviceType = val;
    emit this->deviceTypeChanged();
}

QString Device::getOPCUrl() const {
    return this->device.OPCUrl;
}

void Device::setOPCUrl(const QString &val) {
    this->device.OPCUrl = val;
    emit this->opcUrlChanged();
}

QString Device::getIpAddress() const {
    return this->device.IPAddress;
}

void Device::setIpAddress(const QString &val) {
    this->device.IPAddress = val;
    emit this->ipAddressChanged();
}

QString Device::getNetmask() const {
    return this->device.SubnetMask;
}

void Device::setNetmask(const QString &val) {
    this->device.SubnetMask = val;
    emit this->netmaskChanged();
}

QString Device::getGateway() const {
    return this->device.Gateway;
}

void Device::setGateway(const QString &val) {
    this->device.Gateway = val;
    emit this->gatewayChanged();
}

util::types::Device Device::getDevice() {
    return this->device;
}

void Device::setDevice(const util::types::Device &val) {
    this->device = val;
}

SensorList *Device::getSensorList() {
    this->sensorList->initialize();
    return this->sensorList;
}

RecordList *Device::getRecordList() {
    this->recordList->initialize();
    return this->recordList;
}
