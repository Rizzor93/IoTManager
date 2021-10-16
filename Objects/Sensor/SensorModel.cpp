#include "SensorModel.h"

SensorModel::SensorModel(QObject *parent) : QAbstractListModel(parent) {
}

int SensorModel::rowCount(const QModelIndex &parent) const {
    if (this->sensorList)
        return this->sensorList->count();
    return 0;
}

QVariant SensorModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || !this->sensorList)
        return {};

    auto item = this->sensorList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
            return {item->getDeviceID()};
        case deviceTypeRole:
            return {static_cast<int>(this->sensorList->getDeviceType())};
        case deviceTypeNameRole: {
            switch (this->sensorList->getDeviceType()) {
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
        case sensorIDRole:
            return {item->getSensorID()};
        case nameRole:
            return {item->getName()};
        case dataTypeRole:
            return {static_cast<int>(item->getSensorDataType())};
        case dataTypeNameRole: {
            switch (item->getSensorDataType()) {
                case util::types::SensorDataType::BOOL:
                    return {"BOOL"};
                case util::types::SensorDataType::BYTE:
                    return {"BYTE"};
                case util::types::SensorDataType::INT:
                    return {"INT"};
                case util::types::SensorDataType::FLOAT:
                    return {"FLOAT"};
                case util::types::SensorDataType::DOUBLE:
                    return {"DOUBLE"};
                case util::types::SensorDataType::STRING:
                    return {"STRING"};
                case util::types::SensorDataType::DATETIME:
                    return {"DATETIME"};
                default:
                    return {""};
            }
        }
            // GPIO
        case GPIOTypeRole:
            return {static_cast<int>(item->getGPIOType())};
        case GPIOTypeNameRole: {
            if (item->getGPIOType() == util::types::GPIOType::Input)
                return {"Input"};
            if (item->getGPIOType() == util::types::GPIOType::Output)
                return {"Output"};
            if (item->getGPIOType() == util::types::GPIOType::AnalogInput)
                return {"AnalogInput"};
            if (item->getGPIOType() == util::types::GPIOType::AnalogOutput)
                return {"AnalogOutput"};
        }
        case GPIONumRole:
            return {item->getGPIONum()};
        case pullUpResistorRole:
            return {item->getPullUpResistor()};
            // PLC
        case plcDataAreaRole:
            return {static_cast<int>(item->getPlcDataArea())};
        case plcDataAreaNameRole: {
            if (item->getPlcDataArea() == util::types::PLCDataArea::DB)
                return {"DB"};
            if (item->getPlcDataArea() == util::types::PLCDataArea::MK)
                return {"MK"};
            if (item->getPlcDataArea() == util::types::PLCDataArea::PE)
                return {"PE"};
            if (item->getPlcDataArea() == util::types::PLCDataArea::PA)
                return {"PA"};
            if (item->getPlcDataArea() == util::types::PLCDataArea::CT)
                return {"CT"};
        }
        case dataOffsetRole:
            return {item->getDataOffset()};
        case boolIndexRole:
            return {item->getBoolIndex()};
        case dbNumRole:
            return {item->getDbNum()};
            // OPC
        case nodeIDRole:
            return {item->getNodeID()};

        case sensorRole:
            return QVariant::fromValue<QObject *>(item);
        default:
            break;
    }

    return {};
}

bool SensorModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!this->sensorList)
        return false;

    QVector<int> roles;
    roles << role;

    auto item = this->sensorList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
        case sensorIDRole:
            break;
        case nameRole:
            if (item->getName() != value.toString() && value.toString() != "") {
                item->setName(value.toString());
                item->update();
            } else return false;
            break;
        case dataTypeRole:
            roles << dataTypeNameRole;
            if (static_cast<int>(item->getSensorDataType()) != value.toInt()) {
                item->setSensorDataType(static_cast<util::types::SensorDataType>(value.toInt()));
                item->update();
            } else return false;
            break;
        case dataTypeNameRole:
            break;
            // GPIO
        case GPIOTypeRole:
            roles << GPIOTypeNameRole;
            if (static_cast<int>(item->getGPIOType()) != value.toInt()) {
                item->setGPIOType(static_cast<util::types::GPIOType>(value.toInt()));
                item->update();
            } else return false;
            break;
        case GPIONumRole:
            if (item->getGPIONum() != value.toInt()) {
                item->setGPIONum(value.toInt());
                item->update();
            } else return false;
            break;
        case pullUpResistorRole:
            if (item->getPullUpResistor() != value.toBool()) {
                item->setPullUpResistor(value.toBool());
                item->update();
            } else return false;
            break;
            // PLC
        case plcDataAreaRole:
            roles << plcDataAreaRole;
            if (static_cast<int>(item->getPlcDataArea()) != value.toInt()) {
                item->setPlcDataArea(static_cast<util::types::PLCDataArea>(value.toInt()));
                item->update();
            } else return false;
            break;
        case plcDataAreaNameRole:
            break;
        case dataOffsetRole:
            if (item->getDataOffset() != value.toInt()) {
                item->setDataOffset(value.toInt());
                item->update();
            } else return false;
            break;
        case boolIndexRole:
            if (item->getBoolIndex() != value.toInt()) {
                item->setBoolIndex(value.toInt());
                item->update();
            } else return false;
            break;
        case dbNumRole:
            if (item->getDbNum() != value.toInt()) {
                item->setDbNum(value.toInt());
                item->update();
            } else return false;
            break;
            // OPC
        case nodeIDRole:
            if (item->getNodeID() != value.toString() && value.toString() != "") {
                item->setNodeID(value.toString());
                item->update();
            } else return false;
            break;
        default:
            break;
    }
    emit dataChanged(index, index, roles);
    return true;
}

Qt::ItemFlags SensorModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> SensorModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[deviceIDRole] = "deviceID";
    names[deviceTypeRole] = "deviceType";
    names[deviceTypeNameRole] = "deviceTypeName";
    names[sensorIDRole] = "sensorID";
    names[nameRole] = "name";
    names[dataTypeRole] = "sensorDataType";
    names[dataTypeNameRole] = "sensorDataTypeName";
    // GPIO
    names[GPIOTypeRole] = "gpioType";
    names[GPIOTypeNameRole] = "gpioTypeName";
    names[GPIONumRole] = "gpioNum";
    names[pullUpResistorRole] = "pullUpResistor";
    // PLC
    names[plcDataAreaRole] = "plcDataArea";
    names[plcDataAreaNameRole] = "plcDataAreaName";
    names[dataOffsetRole] = "dataOffset";
    names[boolIndexRole] = "boolIndex";
    names[dbNumRole] = "dbNum";
    // OPC
    names[nodeIDRole] = "nodeID";

    names[sensorRole] = "sensor";

    return names;
}

void SensorModel::modelReset() {
    this->beginResetModel();

    this->sensorList->resetList();

    this->endResetModel();
}

SensorList *SensorModel::getList() {
    return this->sensorList;
}

void SensorModel::setList(SensorList *list) {
    this->beginResetModel();

    this->sensorList = list;
    // Connect the lambda function for insert/remove
    if (this->sensorList) {
        // INSERT LAMBDA FUNCTIONS
        // Insert begin
        connect(this->sensorList, &SensorList::beginInsert, this, [=]() {
            const int index = this->sensorList->count();
            beginInsertRows(QModelIndex(), index, index);
        });
        // Insert end
        connect(this->sensorList, &SensorList::endInsert, this, [=]() {
            endInsertRows();
        });

        // REMOVE LAMBDA FUNCTION
        // Remove begin
        connect(this->sensorList, &SensorList::beginRemove, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        // Remove end
        connect(this->sensorList, &SensorList::endRemove, this, [=]() {
            endRemoveRows();
        });
        // list Changed
        connect(this->sensorList, &SensorList::listChanged, this, &SensorModel::listChanged);
    }

    this->endResetModel();
}

Sensor *SensorModel::at(int index) {
    if (!this->sensorList)
        return nullptr;

    if (!this->sensorList->getList().isEmpty())
        return this->sensorList->getList().at(index);

    return nullptr;
}

void SensorModel::add(Sensor *sensor) {
    if (this->sensorList)
        this->sensorList->create(sensor);
}

void SensorModel::remove(Sensor *sensor) {
    if (this->sensorList)
        this->sensorList->remove(sensor);
}

bool SensorModel::nameExists(const QString &val) {
    return this->sensorList->nameExists(val);
}

QStringList SensorModel::nameList() {
    if (this->sensorList)
        return this->sensorList->nameList();

    return {};
}
