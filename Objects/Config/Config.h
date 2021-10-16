#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QtConcurrent>
#include <QQmlEngine>
#include <QProcess>
#include <iostream>

class Config : public QObject {
Q_OBJECT
public:
    static Config *getInstance(QObject *parent = nullptr) {
        if (config)
            return qobject_cast<Config *>(Config::config);

        auto instance = new Config(parent);
        config = instance;
        return instance;
    }

    static QObject *instance(QQmlEngine *engine, QJSEngine *scriptEngine) {
        Q_UNUSED(scriptEngine)

        if (config) {
            Q_UNUSED(engine)
            return config;
        }

        config = new Config();
        QQmlEngine::setObjectOwnership(config, QQmlEngine::CppOwnership);
        return config;
    }

    QString getHost() {
        return this->settings->value("gRPC/host", "127.0.0.1").toString();

    };

    void setHost(const QString &val) {
        this->settings->setValue("gRPC/host", val);
        emit this->changed();
    };

    QString getPort() {
        return this->settings->value("gRPC/port", "50051").toString();
    };

    void setPort(const QString &val) {
        this->settings->setValue("gRPC/port", val);
        emit this->changed();
    };

    Q_INVOKABLE static void restartApplication() {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }

signals:

    void changed();

private:
    explicit Config(QObject *parent = nullptr);

    static QObject *config;
    QSettings *settings;

};

#endif //CONFIG_H
