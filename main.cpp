#include <iostream>
#include <QMetaEnum>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "utils/utils.h"

#include "Objects/Config/Config.h"
#include "Objects/Config/ConfigModel.h"

#include "Objects/Device/Device.h"
#include "Objects/Device/DeviceList.h"
#include "Objects/Device/DeviceModel.h"

#include "Objects/Sensor/Sensor.h"
#include "Objects/Sensor/SensorList.h"
#include "Objects/Sensor/SensorModel.h"

#include "Objects/Record/Record.h"
#include "Objects/Record/RecordList.h"
#include "Objects/Record/RecordModel.h"
#include "Objects/Record/Sensor/RecordSensor.h"
#include "Objects/Record/Sensor/RecordSensorList.h"
#include "Objects/Record/Sensor/RecordSensorModel.h"

void registerMetaTypes() {
    // STRUCTS
    qRegisterMetaType<util::types::Device>("util::types::Device");
    qRegisterMetaType<util::types::Sensor>("util::types::Sensor");
    qRegisterMetaType<util::types::RecordSensor>("util::types::RecordSensor");
    qRegisterMetaType<util::types::Record>("util::types::Record");
    qRegisterMetaType<util::types::RecordData>("util::types::RecordData");
    qRegisterMetaType<util::types::RecordDataFilter>("util::types::RecordDataFilter");
    // ENUM
    qRegisterMetaType<util::types::DeviceType>("util::types::DeviceType");
    qRegisterMetaType<util::types::SensorDataType>("util::types::SensorDataType");
    qRegisterMetaType<util::types::GPIOType>("util::types::GPIOType");
    qRegisterMetaType<util::types::PLCDataArea>("util::types::PLCDataArea");
    qRegisterMetaType<util::types::RecordType>("util::types::RecordType");
    qRegisterMetaType<util::types::FilterTime>("util::types::FilterTime");
    qRegisterMetaType<util::types::FilterValue>("util::types::FilterValue");
}

void registerTypes() {
    /// CONFIG
    qmlRegisterSingletonType<Config>("IoT", 1, 0, "ConfigSingleTon", Config::instance);
    qmlRegisterType<ConfigModel>("IoT", 1, 0, "ConfigModel");

    /// DEVICE
    qmlRegisterType<Device>("IoT", 1, 0, "Device");
    qmlRegisterUncreatableType<DeviceList>("IoT", 1, 0, "DeviceList",
                                           QStringLiteral("DeviceList should not be created in QML"));
    qmlRegisterType<DeviceModel>("IoT", 1, 0, "DeviceModel");
    /// SENSOR
    qmlRegisterType<Sensor>("IoT", 1, 0, "Sensor");
    qmlRegisterUncreatableType<SensorList>("IoT", 1, 0, "SensorList",
                                           QStringLiteral("SensorList should not be created in QML"));
    qmlRegisterType<SensorModel>("IoT", 1, 0, "SensorModel");
    /// RECORD
    qmlRegisterType<Record>("IoT", 1, 0, "Record");
    qmlRegisterUncreatableType<RecordList>("IoT", 1, 0, "RecordList",
                                           QStringLiteral("RecordList should not be created in QML"));
    qmlRegisterType<RecordModel>("IoT", 1, 0, "RecordModel");
    qmlRegisterType<RecordSensor>("IoT", 1, 0, "RecordSensor");
    qmlRegisterType<RecordSensorList>("IoT", 1, 0, "RecordSensorList");
    qmlRegisterType<RecordSensorModel>("IoT", 1, 0, "RecordSensorModel");
}

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    // Create Gui Application
    QGuiApplication app(argc, argv);

    // RegisterTypes
    registerMetaTypes();
    registerTypes();

    // Create DeviceList
    auto *deviceList = new DeviceList();
    deviceList->initialize();

    // Create ApplicationEngine
    QQmlApplicationEngine engine;
    // Set context
    engine.rootContext()->setContextProperty(QStringLiteral("Devices"), deviceList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    return QGuiApplication::exec();
}
