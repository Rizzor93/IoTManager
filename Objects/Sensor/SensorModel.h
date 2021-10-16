#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include "Sensor.h"
#include "SensorList.h"

class SensorModel : public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(SensorList *list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit SensorModel(QObject *parent = nullptr);

    enum {
        deviceIDRole = Qt::UserRole,
        deviceTypeRole,
        deviceTypeNameRole,
        sensorIDRole,
        nameRole,
        dataTypeRole,
        dataTypeNameRole,
        // GPIO
        GPIOTypeRole,
        GPIOTypeNameRole,
        GPIONumRole,
        pullUpResistorRole,
        // PLC
        plcDataAreaRole,
        plcDataAreaNameRole,
        dataOffsetRole,
        boolIndexRole,
        dbNumRole,
        // OPC
        nodeIDRole,
        // struct
        sensorRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    SensorList *getList();

    void setList(SensorList *list);

public slots:

    Sensor *at(int index);

    void add(Sensor *sensor);

    void remove(Sensor *sensor);

    void modelReset();

    bool nameExists(const QString &val);

    QStringList nameList();

signals:

    void listChanged();

private:
    SensorList *sensorList{};
};

#endif //SENSORMODEL_H
