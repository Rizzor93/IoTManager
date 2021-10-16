#ifndef RECORDSENSOR_H
#define RECORDSENSOR_H

#include "../../Sensor/Sensor.h"

class RecordSensor : public Sensor {
Q_OBJECT
    Q_PROPERTY(util::types::RecordType recordType READ getRecordType WRITE setRecordType NOTIFY recordTypeChanged)
    Q_PROPERTY(QString triggerValueMin READ getTriggerValueMin WRITE setTriggerValueMin NOTIFY triggerValueMinChanged)
    Q_PROPERTY(QString triggerValueMax READ getTriggerValueMax WRITE setTriggerValueMax NOTIFY triggerValueMaxChanged)
    Q_PROPERTY(double interval READ getInterval WRITE setInterval NOTIFY intervalChanged)

    Q_ENUM(util::types::RecordType)

public:
    explicit RecordSensor(QObject *parent = nullptr) { this->setParent(parent); };

    void setRecordID(int val) { this->recordID = val; }

    int getRecordID() { return this->recordID; }

    util::types::RecordType getRecordType() const { return this->recordSensor.RecordType; };

    void setRecordType(const util::types::RecordType &val) {
        this->recordSensor.RecordType = val;
        emit this->recordTypeChanged();
    };

    QString getTriggerValueMin() const { return this->recordSensor.TriggerValueMin; }

    void setTriggerValueMin(const QString &val) {
        this->recordSensor.TriggerValueMin = val;
        emit this->triggerValueMinChanged();
    }

    QString getTriggerValueMax() const { return this->recordSensor.TriggerValueMax; }

    void setTriggerValueMax(const QString &val) {
        this->recordSensor.TriggerValueMax = val;
        emit this->triggerValueMaxChanged();
    }

    double getInterval() const { return this->recordSensor.Interval; }

    void setInterval(const double &val) {
        this->recordSensor.Interval = val;
        emit this->intervalChanged();
    }

    void setRecordSensor(const util::types::RecordSensor &val) {
        this->setSensorID(val.SensorID);
        this->recordSensor.RecordType = val.RecordType;
        this->recordSensor.TriggerValueMin = val.TriggerValueMin;
        this->recordSensor.TriggerValueMax = val.TriggerValueMax;
        this->recordSensor.Interval = val.Interval;
    }

    util::types::RecordSensor getRecordSensor() const {
        util::types::RecordSensor tmp;
        tmp.SensorID = this->getSensorID();
        tmp.RecordType = this->getRecordType();
        tmp.TriggerValueMin = this->getTriggerValueMin();
        tmp.TriggerValueMax = this->getTriggerValueMax();
        tmp.Interval = this->getInterval();

        return tmp;
    }

signals:

    void recordTypeChanged();

    void triggerValueMinChanged();

    void triggerValueMaxChanged();

    void intervalChanged();

private:
    util::types::RecordSensor recordSensor{};
    int recordID{};
};

#endif //RECORDSENSOR_H
