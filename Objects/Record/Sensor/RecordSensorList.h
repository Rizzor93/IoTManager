#ifndef RECORDSENSORLIST_H
#define RECORDSENSORLIST_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include <utility>
#include "RecordSensor.h"

class RecordSensorList : public BaseClass {
Q_OBJECT
    Q_PROPERTY(QList<RecordSensor *> list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit RecordSensorList(QObject *parent = nullptr);

    ~RecordSensorList() override {
        for (auto &s :this->recordSensorList)
            delete s;
        delete this->client;
    }

    void initialize();

    QList<RecordSensor *> getList() const;

    void setList(QList<RecordSensor *> list);

    void resetList();

    int count() const;

    void create(RecordSensor *sensor);

    void remove(RecordSensor *sensor);

    util::types::Record getRecord();

    void setRecord(const util::types::Record &val);

    QList<util::types::RecordSensor> getRecordSensor() const;

private:
    void getSensorsFromServer();

    void attach(RecordSensor *sensor, const util::types::RecordSensor &data);

    void detach(RecordSensor *sensor);

public slots:

signals:

    void listChanged();

    void beginInsert();

    void endInsert();

    void beginRemove(int index);

    void endRemove();

private:
    QList<RecordSensor *> recordSensorList{};
    util::types::Record record{};
};

#endif //RECORDSENSORLIST_H
