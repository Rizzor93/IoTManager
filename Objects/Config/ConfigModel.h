#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QAbstractListModel>
#include "Config.h"

class ConfigModel : public QAbstractListModel {
Q_OBJECT

public:
    explicit ConfigModel(QObject *parent = nullptr);

    enum {
        hostRole = Qt::UserRole,
        portRole,
    };

// Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

// Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

};


#endif //CONFIGMODEL_H
