TEMPLATE = app
TARGET = IoT_Manager
INCLUDEPATH += .
CONFIG += sdk_no_version_check
QT+= widgets qml charts gui quick core concurrent
# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += Objects/BaseClass.h \
    Objects/Device/Device.h \
    Objects/Device/DeviceModel.h \
    Objects/Device/DeviceList.h \
    Objects/Sensor/Sensor.h \
    Objects/Sensor/SensorModel.h \
    Objects/Sensor/SensorList.h \
    Objects/Record/Record.h \
    Objects/Record/RecordList.h \
    Objects/Record/RecordModel.h \
    Objects/Record/Sensor/RecordSensor.h \
    Objects/Record/Sensor/RecordSensorList.h \
    Objects/Record/Sensor/RecordSensorModel.h \
    gRPCClient/grpcClient.h \
    gRPCClient/proto/service/IoT.grpc.pb.h \
    gRPCClient/proto/service/IoT.pb.h \
    utils/utils.h \
    Objects/Config/Config.h \
    Objects/Config/ConfigModel.h

SOURCES += main.cpp \
    Objects/Device/Device.cpp \
    Objects/Device/DeviceModel.cpp \
    Objects/Device/DeviceList.cpp \
    Objects/Sensor/Sensor.cpp \
    Objects/Sensor/SensorModel.cpp \
    Objects/Sensor/SensorList.cpp \
    Objects/Record/Record.cpp \
    Objects/Record/RecordList.cpp \
    Objects/Record/RecordModel.cpp \
    Objects/Record/Sensor/RecordSensorList.cpp \
    Objects/Record/Sensor/RecordSensorModel.cpp \
    gRPCClient/proto/service/IoT.grpc.pb.cc \
    gRPCClient/proto/service/IoT.pb.cc \
    Objects/Config/Config.cpp \
    Objects/Config/ConfigModel.cpp

DISTFILES += gRPCClient/proto/IoT.proto \
        qml/qtquickcontrols2.conf \
        config.ini

RESOURCES += qml/rcc.qrc


INCLUDEPATH += $$PWD/../../Qt/Tools/grpc_shared/include
DEPENDPATH += $$PWD/../../Qt/Tools/grpc_shared/include

macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lgrpc++.1.41.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lprotobuf.3.17.3.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lgrpc.19.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -laddress_sorting.19.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lre2
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_hash.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_city.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_wyhash.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_raw_hash_set.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_hashtablez_sampler.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_exponential_biased.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_statusor.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_bad_variant_access.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lgpr.19.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -lupb.19.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_status.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_cord.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_str_format_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_synchronization.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_stacktrace.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_symbolize.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_debugging_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_demangle_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_graphcycles_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_malloc_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_time.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_strings.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_throw_delegate.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_strings_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_base.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_spinlock_wait.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_int128.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_civil_time.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_time_zone.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_bad_optional_access.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_raw_logging_internal.2103.0.0
macx: LIBS += -L$$PWD/../../Qt/Tools/grpc_shared/lib/ -labsl_log_severity.2103.0.0
