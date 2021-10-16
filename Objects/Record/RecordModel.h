#ifndef RECORDMODEL_H
#define RECORDMODEL_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include "RecordList.h"

class RecordModel : public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(RecordList *list READ getList WRITE setList NOTIFY listChanged)

public:
    explicit RecordModel(QObject *parent = nullptr);

    enum {
        deviceIDRole = Qt::UserRole,
        recordIDRole,
        nameRole,
        runningRole,
        recordRole,
        recordSensorListRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    RecordList *getList();

    void setList(RecordList *list);

public slots:

    Record *at(int index);

    void add(Record *record);

    void remove(Record *record);

    void modelReset();

    bool nameExists(const QString &val);

signals:

    void listChanged();

private:
    RecordList *recordList{};
};


#endif //RECORDMODEL_H
