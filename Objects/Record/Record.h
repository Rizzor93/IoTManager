#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <QList>
#include <QString>
#include "../BaseClass.h"
#include "../../utils/utils.h"
#include "Sensor/RecordSensorList.h"

using namespace std;

class Record : public BaseClass {
Q_OBJECT
    Q_PROPERTY(int recordID READ getRecordID WRITE setRecordID NOTIFY recordIDChanged)
    Q_PROPERTY(int deviceID READ getDeviceID WRITE setDeviceID NOTIFY deviceIDChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool running READ getRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(
            RecordSensorList *recordSensorList READ getRecordSensorList WRITE setRecordSensorList NOTIFY recordSensorListChanged)

public:
    explicit Record(QObject *parent = nullptr);

    ~Record() override {
        delete this->recordSensorList;
        delete this->client;
    }

    void initialize();

    Q_INVOKABLE void update();

    void remove();

    int getRecordID() const;

    void setRecordID(const int &val);

    int getDeviceID() const;

    void setDeviceID(const int &val);

    QString getName() const;

    void setName(const QString &val);

    bool getRunning() const;

    void setRunning(const bool &val);

    util::types::Record getRecord();

    void setRecord(const util::types::Record &val);

    RecordSensorList *getRecordSensorList() { return this->recordSensorList; }

    void setRecordSensorList(RecordSensorList *list) {
        this->recordSensorList = list;
        emit this->recordSensorListChanged();
    }

public slots:

signals:

    void recordIDChanged();

    void deviceIDChanged();

    void nameChanged();

    void runningChanged();

    void recordSensorListChanged();

private:
    util::types::Record record{};
    RecordSensorList *recordSensorList{};
};


#endif //RECORD_H
