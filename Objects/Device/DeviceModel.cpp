#include "DeviceModel.h"

DeviceModel::DeviceModel(QObject *parent) : QAbstractListModel(parent) {
}

int DeviceModel::rowCount(const QModelIndex &parent) const {
    if (this->deviceList)
        return this->deviceList->count();
    return 0;
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || !this->deviceList)
        return {};

    auto item = this->deviceList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
            return {item->getDeviceID()};
        case nameRole:
            return {item->getName()};
        case locationRole:
            return {item->getLocation()};
        case deviceTypeRole:
            return {static_cast<int>(item->getDeviceType())};
        case deviceTypeNameRole: {
            switch (item->getDeviceType()) {
                case util::types::DeviceType::PLC_Siemens:
                    return {"PLC_Siemens"};
                case util::types::DeviceType::PLC_Beckhoff:
                    return {"PLC_Beckhoff"};
                case util::types::DeviceType::PLC_WAGO:
                    return {"PLC_WAGO"};
                case util::types::DeviceType::OPC:
                    return {"OPC"};
                case util::types::DeviceType::ARDUINO:
                    return {"Arduino"};
                case util::types::DeviceType::RASPBERRYPI:
                    return {"RaspberryPi"};
                default:
                    break;
            }
        }
        case opcUrlRole:
            return {item->getOPCUrl()};
        case ipAddressRole:
            return {item->getIpAddress()};
        case netmaskRole:
            return {item->getNetmask()};
        case gatewayRole:
            return {item->getGateway()};
        case deviceRole:
            return QVariant::fromValue<Device *>(item);
        case sensorListRole:
            return QVariant::fromValue<SensorList *>(item->getSensorList());
        case recordListRole:
            return QVariant::fromValue<RecordList *>(item->getRecordList());
        default:
            break;
    }
    return {};
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!this->deviceList)
        return false;

    QVector<int> roles;
    roles << role;

    auto const item = this->deviceList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
            if (item->getDeviceID() != value.toInt()) {
                item->setDeviceID(value.toInt());
                item->update();
            } else return false;
            break;
        case nameRole:
            if (item->getName() != value.toString() && value.toString() != "") {
                item->setName(value.toString());
                item->update();
            } else return false;
            break;
        case locationRole:
            if (item->getLocation() != value.toString() && value.toString() != "") {
                item->setLocation(value.toString());
                item->update();
            } else return false;
            break;
        case deviceTypeRole:
            if (static_cast<int>(item->getDeviceType()) != value.toInt()) {
                item->setDeviceType(static_cast<util::types::DeviceType>(value.toInt()));
                item->update();
            } else return false;
            break;
        case opcUrlRole:
            if (item->getOPCUrl() != value.toString() && value.toString() != "") {
                item->setOPCUrl(value.toString());
                item->update();
            } else return false;
            break;
        case ipAddressRole:
            if (item->getIpAddress() != value.toString() && value.toString() != "") {
                item->setIpAddress(value.toString());
                item->update();
            } else return false;
            break;
        case netmaskRole:
            if (item->getNetmask() != value.toString() && value.toString() != "") {
                item->setNetmask(value.toString());
                item->update();
            } else return false;
            break;
        case gatewayRole:
            if (item->getGateway() != value.toString() && value.toString() != "") {
                item->setGateway(value.toString());
                item->update();
            } else return false;
            break;
        default:
            break;
    }

    emit dataChanged(index, index, roles);

    return true;
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> DeviceModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[deviceIDRole] = "deviceID";
    names[nameRole] = "name";
    names[locationRole] = "location";
    names[deviceTypeRole] = "deviceType";
    names[deviceTypeNameRole] = "deviceTypeName";
    names[opcUrlRole] = "opcUrl";
    names[ipAddressRole] = "ipAddress";
    names[gatewayRole] = "gateway";
    names[netmaskRole] = "subnetMask";
    names[deviceRole] = "device";
    names[sensorListRole] = "sensorList";
    names[recordListRole] = "recordList";

    return names;
}

void DeviceModel::modelReset() {
    this->beginResetModel();

    this->deviceList->resetList();

    this->endResetModel();
}

DeviceList *DeviceModel::getList() {
    return this->deviceList;
}

void DeviceModel::setList(DeviceList *list) {
    this->beginResetModel();

    this->deviceList = list;
    // Connect the lambda function for insert/remove
    if (this->deviceList) {
        // INSERT LAMBDA FUNCTIONS
        // Insert begin
        connect(this->deviceList, &DeviceList::beginInsert, this, [=]() {
            const int index = this->deviceList->count();
            beginInsertRows(QModelIndex(), index, index);
        });
        // Insert end
        connect(this->deviceList, &DeviceList::endInsert, this, [=]() {
            endInsertRows();
        });

        // REMOVE LAMBDA FUNCTION
        // Remove begin
        connect(this->deviceList, &DeviceList::beginRemove, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        // Remove end
        connect(this->deviceList, &DeviceList::beginRemove, this, [=]() {
            endRemoveRows();
        });
        // list Changed
        connect(this->deviceList, &DeviceList::listChanged, this, &DeviceModel::listChanged);
    }

    this->endResetModel();
}

Device *DeviceModel::at(int index) {
    if (!this->deviceList)
        return nullptr;

    if (!this->deviceList->getList().isEmpty())
        return this->deviceList->getList().at(index);

    return nullptr;
}

void DeviceModel::add(Device *device) {
    if (this->deviceList)
        this->deviceList->create(device);
}

void DeviceModel::remove(Device *device) {
    if (this->deviceList)
        this->deviceList->remove(device);
}

bool DeviceModel::nameExists(const QString &val) {
    return this->deviceList->nameExists(val);
}
