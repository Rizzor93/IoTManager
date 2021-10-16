#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include "Device.h"
#include "DeviceList.h"

class DeviceModel : public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(DeviceList *list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit DeviceModel(QObject *parent = nullptr);

    ~DeviceModel() override {
        delete this->deviceList;
    }

    enum {
        deviceIDRole = Qt::UserRole,
        nameRole,
        locationRole,
        deviceTypeRole,
        deviceTypeNameRole,
        opcUrlRole,
        ipAddressRole,
        netmaskRole,
        gatewayRole,
        // struct
        deviceRole,
        // SensorList*
        sensorListRole,
        // RecordList*
        recordListRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    DeviceList *getList();

    void setList(DeviceList *list);

public slots:

    Device *at(int index);

    void add(Device *device);

    void remove(Device *device);

    void modelReset();

    bool nameExists(const QString &val);

signals:

    void listChanged();

private:
    DeviceList *deviceList;
};

#endif //DEVICEMODEL_H
