#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <QObject>
#include <QList>
#include <QString>
#include "../BaseClass.h"
#include "../../utils/utils.h"

class Sensor : public BaseClass {
Q_OBJECT
    Q_PROPERTY(int sensorID READ getSensorID WRITE setSensorID NOTIFY sensorIDChanged)
    Q_PROPERTY(int deviceID READ getDeviceID WRITE setDeviceID NOTIFY deviceIDChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(
            util::types::SensorDataType sensorDataType READ getSensorDataType WRITE setSensorDataType NOTIFY sensorDataTypeChanged)
    // GPIO
    Q_PROPERTY(int gpioNum READ getGPIONum WRITE setGPIONum NOTIFY gpioNumChanged)
    Q_PROPERTY(util::types::GPIOType gpioType READ getGPIOType WRITE setGPIOType NOTIFY gpioTypeChanged)
    Q_PROPERTY(bool pullUpResistor READ getPullUpResistor WRITE setPullUpResistor NOTIFY pullUpResistorChanged)
    // PLC
    Q_PROPERTY(util::types::PLCDataArea plcDataArea READ getPlcDataArea WRITE setPlcDataArea NOTIFY plcDataAreaChanged)
    Q_PROPERTY(int dataOffset READ getDataOffset WRITE setDataOffset NOTIFY dataOffsetChanged)
    Q_PROPERTY(int boolIndex READ getBoolIndex WRITE setBoolIndex NOTIFY boolIndexChanged)
    Q_PROPERTY(int dbNum READ getDbNum WRITE setDbNum NOTIFY dbNumChanged)
    // OPC
    Q_PROPERTY(QString nodeID READ getNodeID WRITE setNodeID NOTIFY nodeIDChanged)

    Q_ENUM(util::types::SensorDataType)

    Q_ENUM(util::types::PLCDataArea)

    Q_ENUM(util::types::GPIOType)

public:
    explicit Sensor(QObject *parent = nullptr);

    ~Sensor() override {
        delete this->client;
    }

    void initialize();

    Q_INVOKABLE void update();

    void remove();

    int getDeviceID() const;

    void setDeviceID(const int &val);

    int getSensorID() const;

    void setSensorID(const int &val);

    QString getName() const;

    void setName(const QString &val);

    util::types::SensorDataType getSensorDataType() const;

    void setSensorDataType(const util::types::SensorDataType &val);

    util::types::Sensor getSensor();

    void setSensor(const util::types::Sensor &val);

    /// GPIO
    int getGPIONum() const;

    void setGPIONum(const int &val);

    util::types::GPIOType getGPIOType() const;

    void setGPIOType(const util::types::GPIOType &val);

    bool getPullUpResistor() const;

    void setPullUpResistor(const bool &val);

    /// PLC
    util::types::PLCDataArea getPlcDataArea() const;

    void setPlcDataArea(const util::types::PLCDataArea &val);

    int getDataOffset() const;

    void setDataOffset(const int &val);

    int getBoolIndex() const;

    void setBoolIndex(const int &val);

    int getDbNum() const;

    void setDbNum(const int &val);

    /// OPC
    QString getNodeID() const;

    void setNodeID(const QString &val);

signals:

    void sensorIDChanged();

    void deviceIDChanged();

    void nameChanged();

    void sensorDataTypeChanged();

    void gpioNumChanged();

    void gpioTypeChanged();

    void pullUpResistorChanged();

    void plcDataAreaChanged();

    void dataOffsetChanged();

    void boolIndexChanged();

    void dbNumChanged();

    void nodeIDChanged();

private:
    util::types::Sensor sensor;
};

#endif //SENSOR_H
