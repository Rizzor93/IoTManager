#include "RecordModel.h"

RecordModel::RecordModel(QObject *parent) : QAbstractListModel(parent) {
}

int RecordModel::rowCount(const QModelIndex &parent) const {
    if (this->recordList)
        return this->recordList->count();
    return 0;
}

QVariant RecordModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || !this->recordList)
        return {};

    auto item = this->recordList->getList().at(index.row());

    switch (role) {
        case deviceIDRole:
            return {item->getDeviceID()};
        case recordIDRole:
            return {item->getRecordID()};
        case nameRole:
            return {item->getName()};
        case runningRole:
            return {item->getRunning()};
        case recordRole:
            return QVariant::fromValue<Record *>(item);
        case recordSensorListRole:
            return QVariant::fromValue<RecordSensorList *>(item->getRecordSensorList());
        default:
            break;
    }

    return {};
}

bool RecordModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!this->recordList)
        return false;

    QVector<int> roles;
    roles << role;

    auto item = this->recordList->getList().at(index.row());
    switch (role) {
        case nameRole:
            if (item->getName() != value.toString() && value.toString() != "") {
                item->setName(value.toString());
                item->update();
            } else return false;
            break;
        case runningRole:
            if (item->getRunning() != value.toBool()) {
                item->setRunning(value.toBool());
                item->update();
            } else return false;
            break;
        default:
            break;
    }

    emit dataChanged(index, index, roles);

    return true;
}

Qt::ItemFlags RecordModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> RecordModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[deviceIDRole] = "deviceID";
    names[recordIDRole] = "recordID";
    names[nameRole] = "name";
    names[runningRole] = "running";
    names[recordSensorListRole] = "recordSensorList";
    names[recordRole] = "record";

    return names;
}

void RecordModel::modelReset() {
    this->beginResetModel();

    this->recordList->resetList();

    this->endResetModel();
}

RecordList *RecordModel::getList() {
    return this->recordList;
}

void RecordModel::setList(RecordList *list) {
    this->beginResetModel();

    this->recordList = list;
    // Connect the lambda function for insert/remove
    if (this->recordList) {
        // INSERT LAMBDA FUNCTIONS
        // Insert begin
        connect(this->recordList, &RecordList::beginInsert, this, [=]() {
            const int index = this->recordList->count();
            beginInsertRows(QModelIndex(), index, index);
        });
        // Insert end
        connect(this->recordList, &RecordList::endInsert, this, [=]() {
            endInsertRows();
        });

        // REMOVE LAMBDA FUNCTION
        // Remove begin
        connect(this->recordList, &RecordList::beginRemove, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        // Remove end
        connect(this->recordList, &RecordList::endRemove, this, [=]() {
            endRemoveRows();
        });
        // list Changed
        connect(this->recordList,&RecordList::listChanged,this,&RecordModel::listChanged);
    }

    this->endResetModel();
}

Record *RecordModel::at(int index) {
    if (!this->recordList)
        return nullptr;

    if (!this->recordList->getList().isEmpty())
        return this->recordList->getList().at(index);

    return nullptr;
}

void RecordModel::add(Record *record) {
    if (this->recordList)
        this->recordList->create(record);
}

void RecordModel::remove(Record *record) {
    if (this->recordList)
        this->recordList->remove(record);
}

bool RecordModel::nameExists(const QString &val) {
    return this->recordList->nameExists(val);
}
