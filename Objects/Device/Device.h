#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <QObject>
#include <QList>
#include <QString>
#include "../../utils/utils.h"
#include "../BaseClass.h"
#include "../Sensor/SensorList.h"
#include "../Record/RecordList.h"

using namespace std;

class Device : public BaseClass {
Q_OBJECT
    Q_PROPERTY(int deviceID READ getDeviceID WRITE setDeviceID NOTIFY deviceIDChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString location READ getLocation WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(util::types::DeviceType deviceType READ getDeviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(QString opcUrl READ getOPCUrl WRITE setOPCUrl NOTIFY opcUrlChanged)
    Q_PROPERTY(QString ipAddress READ getIpAddress WRITE setIpAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(QString gateway READ getGateway WRITE setGateway NOTIFY gatewayChanged)
    Q_PROPERTY(QString subnetMask READ getNetmask WRITE setNetmask NOTIFY netmaskChanged)
    Q_PROPERTY(SensorList *sensorList READ getSensorList NOTIFY sensorListChanged)
    Q_PROPERTY(RecordList *recordList READ getRecordList NOTIFY recordListChanged)

    Q_ENUM(util::types::DeviceType)

public:

    explicit Device(QObject *parent = nullptr);

    ~Device() override {
        delete this->client;
    };

    void initialize();

    Q_INVOKABLE void update();

    void remove();

    int getDeviceID() const;

    void setDeviceID(const int &val);

    QString getName() const;

    void setName(const QString &val);

    QString getLocation() const;

    void setLocation(const QString &val);

    util::types::DeviceType getDeviceType() const;

    void setDeviceType(const util::types::DeviceType &val);

    QString getOPCUrl() const;

    void setOPCUrl(const QString &val);

    QString getIpAddress() const;

    void setIpAddress(const QString &val);

    QString getNetmask() const;

    void setNetmask(const QString &val);

    QString getGateway() const;

    void setGateway(const QString &val);

    util::types::Device getDevice();

    void setDevice(const util::types::Device &val);

    SensorList *getSensorList();

    RecordList *getRecordList();

signals:

    void deviceIDChanged();

    void nameChanged();

    void locationChanged();

    void deviceTypeChanged();

    void opcUrlChanged();

    void ipAddressChanged();

    void gatewayChanged();

    void netmaskChanged();

    void sensorListChanged();

    void recordListChanged();

private:
    util::types::Device device{};
    SensorList *sensorList{};
    RecordList *recordList{};
};

#endif //DEVICE_H
