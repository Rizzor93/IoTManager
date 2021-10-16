#include "ConfigModel.h"

ConfigModel::ConfigModel(QObject *parent) : QAbstractListModel(parent) {
}

int ConfigModel::rowCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ConfigModel::data(const QModelIndex &index, int role) const {
    auto item = Config::getInstance();

    if (role == hostRole)
        return item->getHost();
    else if (role == portRole)
        return item->getPort();

    return {};
}

bool ConfigModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    auto item = Config::getInstance();
    QVector<int> roles;
    roles << role;

    if (role == hostRole) {
        if (item->getHost() != value.toString() && value.toString() != "") {
            item->setHost(value.toString());
        }
    } else if (role == portRole) {
        if (item->getPort() != value.toString() && value.toString() != "") {
            item->setPort(value.toString());
        }
    }

    emit dataChanged(index, index, roles);

    return true;
}

Qt::ItemFlags ConfigModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ConfigModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[hostRole] = "host";
    names[portRole] = "port";

    return names;
}
