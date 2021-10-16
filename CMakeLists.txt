#################################################################
################### CMAKE OPTIONS ###############################
#################################################################
cmake_minimum_required(VERSION 3.20)
project(IoT_Manager)
set(CMAKE_CXX_STANDARD 20)
set(DCMAKE_OSX_ARCHITECTURES=x86_64)
# Set Path to libs
set(Qt5_DIR "")
set(gRPC_DIR "")
set(absl_DIR "")
set(Protobuf_DIR "")
set(OPENSSL_ROOT_DIR "")
#
#################################################################
############################## LIBS #############################
#################################################################
# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Qml Charts Quick Concurrent)
set(REQUIRED_LIBS_QUALIFIED Qt::Core Qt::Gui Qt::Widgets Qt::Qml Qt::Charts Qt::Concurrent)
set(QT_DEBUG_PLUGINS=1)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
message(STATUS "Using Qt ${QT_VERSION}")
# Protobuf
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using Protobuf ${Protobuf_VERSION}")
# gRPC
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
# OpenSSL
find_package(OpenSSL)
message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
#################################################################
####################### IoT_Manager #############################
#################################################################
#
add_executable(IoT_Manager
        main.cpp
        ############ src Qml(compiled .qml files)
        qml/src.cpp
        ############ gRPC
        gRPCClient/grpcClient.h
        gRPCClient/proto/service/IoT.grpc.pb.cc
        gRPCClient/proto/service/IoT.grpc.pb.h
        gRPCClient/proto/service/IoT.pb.cc
        gRPCClient/proto/service/IoT.pb.h
        ############ utils
        utils/utils.h
        ############ Qml-Objects
        # Base
        Objects/BaseClass.h
        # Config
        Objects/Config/Config.h
        Objects/Config/ConfigModel.cpp Objects/Config/ConfigModel.h
        # Device
        Objects/Device/Device.cpp Objects/Device/Device.h
        Objects/Device/DeviceList.cpp Objects/Device/DeviceList.h
        Objects/Device/DeviceModel.cpp Objects/Device/DeviceModel.h
        # Sensor
        Objects/Sensor/Sensor.cpp Objects/Sensor/Sensor.h
        Objects/Sensor/SensorList.cpp Objects/Sensor/SensorList.h
        Objects/Sensor/SensorModel.cpp Objects/Sensor/SensorModel.h
        # Record
        Objects/Record/Record.cpp Objects/Record/Record.h
        Objects/Record/RecordList.cpp Objects/Record/RecordList.h
        Objects/Record/RecordModel.cpp Objects/Record/RecordModel.h
        Objects/Record/Sensor/RecordSensor.h
        Objects/Record/Sensor/RecordSensorList.cpp Objects/Record/Sensor/RecordSensorList.h
        Objects/Record/Sensor/RecordSensorModel.cpp Objects/Record/Sensor/RecordSensorModel.h

        Objects/Config/Config.cpp)

# link the libs
target_link_libraries(IoT_Manager gRPC::grpc++ ${REQUIRED_LIBS_QUALIFIED})
# target_link_libraries(IoT_Manager OpenSSL::SSL)
# target_link_libraries(IoT_Manager OpenSSL::Crypto)