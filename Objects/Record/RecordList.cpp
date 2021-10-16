#include "RecordList.h"

RecordList::RecordList(QObject *parent) {
    this->setParent(parent);
    this->connectGRPC();
}

void RecordList::initialize() {
    this->getRecordsFromServer();
}

void RecordList::getRecordsFromServer() {
    QList<util::types::Record> tmp = this->client->GetRecords(this->device.ID);

    for (auto &r : this->recordList)
        this->detach(r);

    for (auto const &r : tmp)
        this->attach(new Record(), r);

}

QList<Record *> RecordList::getList() const {
    return this->recordList;
}

void RecordList::setList(QList<Record *> list) {
    this->recordList = std::move(list);
    emit this->listChanged();
}

void RecordList::resetList() {
    qDeleteAll(this->recordList.begin(), this->recordList.end());
    this->recordList.clear();
}

int RecordList::count() const {
    return this->recordList.count();
}

void RecordList::create(Record *record) {
    this->client->CreateRecord(record->getRecord());

    this->getRecordsFromServer();
}

void RecordList::remove(Record *record) {
    if (!this->recordList.empty()) {

        emit this->beginRemove(this->recordList.indexOf(record));
        this->recordList.removeOne(record);
        record->remove();

        emit this->endRemove();
    }
    emit this->listChanged();
}

bool RecordList::nameExists(const QString &val) {
    for (auto const &r : this->recordList) {
        if (r->getName() == val)
            return true;
    }
    return false;
}

void RecordList::attach(Record *record, const util::types::Record &data) {
    emit this->beginInsert();

    record->setRecord(data);
    record->initialize();

    connect(record, &Record::changed, this, &RecordList::recordChanged);
    connect(this, &RecordList::update, record, &Record::initialize);

    this->recordList.push_back(record);
    emit this->endInsert();
}

void RecordList::detach(Record *record) {
    emit this->beginRemove(this->recordList.indexOf(record));

    this->recordList.removeOne(record);
    delete record;

    emit this->endRemove();
}

void RecordList::setDevice(const util::types::Device &val) {
    this->device = val;
}

util::types::DeviceType RecordList::getDeviceType() const {
    return this->device.DeviceType;
}




