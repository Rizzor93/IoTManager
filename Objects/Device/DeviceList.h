#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include "Device.h"
#include "../BaseClass.h"

class DeviceList : public BaseClass {
Q_OBJECT
    Q_PROPERTY(QList<Device *> list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit DeviceList(QObject *parent = nullptr);

    ~DeviceList() override {
        for (auto &d : this->deviceList)
            delete d;

        delete this->client;
    };

    void initialize();

    QList<Device *> getList() const;

    void setList(QList<Device *> list);

    void resetList();

    int count() const;

    void create(Device *device);

    void remove(Device *device);

    bool nameExists(const QString &val);


private:
    void getDevicesFromServer();

    void attach(Device *device, const util::types::Device &data);

    void detach(Device *device);

public slots:


signals:

    void listChanged();

    void beginInsert();

    void endInsert();

    void beginRemove(int index);

    void endRemove();

    void createFinish();

private:
    QList<Device *> deviceList;
};

#endif //DEVICELIST_H
