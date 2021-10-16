#ifndef RECORDSENSORMODEL_H
#define RECORDSENSORMODEL_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include "RecordSensor.h"
#include "RecordSensorList.h"

class RecordSensorModel : public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(RecordSensorList *list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit RecordSensorModel(QObject *parent = nullptr);

    enum {
        deviceIDRole = Qt::UserRole,
        recordIDRole,
        nameRole,
        recordTypeRole,
        recordTypeNameRole,
        triggerValueMinRole,
        triggerValueMaxRole,
        intervalRole,
        sensorRole,
        dataTypeRole,
        dataTypeNameRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    RecordSensorList *getList();

    void setList(RecordSensorList *val);

public slots:

    RecordSensor *at(int index);

    void add(RecordSensor *sensor);

    void remove(RecordSensor *sensor);

    void modelReset();

signals:

    void listChanged();

private:
    RecordSensorList *sensorList;
};

#endif //RECORDSENSORMODEL_H
