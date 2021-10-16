#include "DeviceList.h"

#include <utility>

DeviceList::DeviceList(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
}

void DeviceList::initialize() {
    this->getDevicesFromServer();
}

void DeviceList::getDevicesFromServer() {
    QList<util::types::Device> tmp = this->client->GetDevices();
    QList<util::types::Device> old{};
    QList<util::types::Device> newDevices{};

    for (auto const &d : this->deviceList)
        old << d->getDevice();

    for (auto const &d : tmp)
        newDevices << d;

    for (const util::types::Device &device : newDevices) {
        if (std::find(old.begin(), old.end(), device) == old.end()) {
            this->attach(new Device(), device);
        }
    }

}

QList<Device *> DeviceList::getList() const {
    return this->deviceList;
}

void DeviceList::setList(QList<Device *> list) {
    this->deviceList = std::move(list);
    emit this->listChanged();
}

void DeviceList::resetList() {
    qDeleteAll(this->deviceList.begin(), this->deviceList.end());
    this->deviceList.clear();
}

int DeviceList::count() const {
    return this->deviceList.count();
}

void DeviceList::create(Device *device) {
    this->client->CreateDevice(device->getDevice());

    this->getDevicesFromServer();
}

void DeviceList::remove(Device *device) {
    if (!this->deviceList.empty())
        this->detach(device);

    emit this->listChanged();
}

bool DeviceList::nameExists(const QString &val) {
    for (auto const &r : this->deviceList) {
        if (r->getName() == val)
            return true;
    }
    return false;
}

void DeviceList::attach(Device *device, const util::types::Device &data) {
    emit this->beginInsert();

    device->setDevice(data);
    device->initialize();
    this->deviceList.push_back(device);

    emit this->endInsert();
}

void DeviceList::detach(Device *device) {
    emit this->beginRemove(this->deviceList.indexOf(device));

    this->deviceList.removeOne(device);
    device->remove();

    emit this->endRemove();
}





