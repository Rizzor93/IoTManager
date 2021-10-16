#include "RecordSensorModel.h"

RecordSensorModel::RecordSensorModel(QObject *parent) : QAbstractListModel(parent) {
}

int RecordSensorModel::rowCount(const QModelIndex &parent) const {
    if (this->sensorList) {
        return this->sensorList->count();
    }
    return 0;
}

QVariant RecordSensorModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || !this->sensorList)
        return {};

    auto item = this->sensorList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
            return {item->getDeviceID()};
        case recordIDRole:
            return {this->sensorList->getRecord().ID};
        case nameRole:
            return {item->getName()};
        case recordTypeRole:
            return {static_cast<int>(item->getRecordType())};
        case recordTypeNameRole: {
            switch (item->getRecordType()) {
                case util::types::RecordType::EQUAL:
                    return {"EQUAL"};
                case util::types::RecordType::ODD:
                    return {"ODD"};
                case util::types::RecordType::SMALLER_THEN:
                    return {"SMALLER_THEN"};
                case util::types::RecordType::BIGGER_THEN:
                    return {"BIGGER_THEN"};
                case util::types::RecordType::RANGE:
                    return {"RANGE"};
                case util::types::RecordType::ALWAYS:
                    return {"ALWAYS"};
                default:
                    break;
            }
        }
        case triggerValueMinRole:
            return {item->getTriggerValueMin()};
        case triggerValueMaxRole:
            return {item->getTriggerValueMax()};
        case intervalRole:
            return {item->getInterval()};
        case sensorRole:
            return QVariant::fromValue<RecordSensor *>(item);
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
        default:
            break;
    }

    return {};
}

bool RecordSensorModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!this->sensorList)
        return false;

    QVector<int> roles;
    roles << role;

    auto const item = this->sensorList->getList().at(index.row());

    switch (role) {
        case recordTypeRole:
            if (static_cast<int>(item->getRecordType()) != value.toInt()) {
                item->setRecordType(static_cast<util::types::RecordType>(value.toInt()));
                item->update();
            } else return false;
            break;
        case triggerValueMinRole:
            if (item->getTriggerValueMin() != value.toString() && value.toString() != "") {
                item->setTriggerValueMin(value.toString());
                item->update();
            } else return false;
            break;
        case triggerValueMaxRole:
            if (item->getTriggerValueMax() != value.toString() && value.toString() != "") {
                item->setTriggerValueMax(value.toString());
                item->update();
            } else return false;
            break;
        case intervalRole:
            if (item->getInterval() != value.toInt()) {
                item->setInterval(value.toInt());
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
        default:
            break;
    }

    emit dataChanged(index, index, roles);

    return true;
}

Qt::ItemFlags RecordSensorModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> RecordSensorModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[deviceIDRole] = "deviceID";
    names[recordIDRole] = "recordID";
    names[nameRole] = "name";
    names[recordTypeRole] = "recordType";
    names[recordTypeNameRole] = "recordTypeName";
    names[triggerValueMinRole] = "triggerValueMin";
    names[triggerValueMaxRole] = "triggerValueMax";
    names[intervalRole] = "interval";
    names[sensorRole] = "sensor";
    names[dataTypeRole] = "sensorDataType";
    names[dataTypeNameRole] = "sensorDataTypeName";
    return names;
}

void RecordSensorModel::modelReset() {
    this->beginResetModel();

    this->sensorList->resetList();

    this->endResetModel();
}

RecordSensorList *RecordSensorModel::getList() {
    return this->sensorList;
}

void RecordSensorModel::setList(RecordSensorList *val) {
    this->beginResetModel();

    this->sensorList = val;
    // Connect the lambda function for insert/remove
    if (this->sensorList) {
        // INSERT LAMBDA FUNCTIONS
        // Insert begin
        connect(this->sensorList, &RecordSensorList::beginInsert, this, [=]() {
            const int index = this->sensorList->count();
            beginInsertRows(QModelIndex(), index, index);
        });
        // Insert end
        connect(this->sensorList, &RecordSensorList::endInsert, this, [=]() {
            endInsertRows();
        });

        // REMOVE LAMBDA FUNCTION
        // Remove begin
        connect(this->sensorList, &RecordSensorList::beginRemove, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        // Remove end
        connect(this->sensorList, &RecordSensorList::endRemove, this, [=]() {
            endRemoveRows();
        });
        // list Changed
        connect(this->sensorList, &RecordSensorList::listChanged, this, &RecordSensorModel::listChanged);
    }

    this->endResetModel();
}

RecordSensor *RecordSensorModel::at(int index) {
    if (!this->sensorList)
        return nullptr;

    if (!this->sensorList->getList().isEmpty())
        return this->sensorList->getList().at(index);

    return nullptr;
}

void RecordSensorModel::add(RecordSensor *sensor) {
    if (this->sensorList)
        this->sensorList->create(sensor);
}

void RecordSensorModel::remove(RecordSensor *sensor) {
    if (this->sensorList)
        this->sensorList->remove(sensor);
}
