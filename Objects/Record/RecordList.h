#ifndef RECORDLIST_H
#define RECORDLIST_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <utility>
#include "Record.h"
#include "Sensor/RecordSensorList.h"
#include "../BaseClass.h"

class RecordList : public BaseClass {
Q_OBJECT
    Q_PROPERTY(QList<Record *> list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit RecordList(QObject *parent = nullptr);

    ~RecordList() override {
        for (auto &s : this->recordList)
            delete s;

        delete this->client;
    }

    void initialize();

    QList<Record *> getList() const;

    void setList(QList<Record *> list);

    void resetList();

    int count() const;

    void create(Record *record);

    void remove(Record *record);

    bool nameExists(const QString &val);

    void setDevice(const util::types::Device &val);

    util::types::DeviceType getDeviceType() const;

private:
    void getRecordsFromServer();

    void attach(Record *record, const util::types::Record &data);

    void detach(Record *record);

public slots:


signals:

    void recordChanged();

    void listChanged();

    void beginInsert();

    void endInsert();

    void beginRemove(int index);

    void endRemove();

    void update();

private:
    QList<Record *> recordList{};
    util::types::Device device{};
};

#endif //RECORDLIST_H
