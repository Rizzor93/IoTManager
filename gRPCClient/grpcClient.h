#ifndef GRPC_CLIENT_GRPCCLIENT_H
#define GRPC_CLIENT_GRPCCLIENT_H

#include <iostream>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "proto/service/IoT.grpc.pb.h"
#include "../utils/utils.h"
#include <QString>
#include <QList>
#include <vector>
#include <google/protobuf/util/time_util.h>

using namespace google;
using namespace grpc;

class gRPCClient {
public:
    explicit gRPCClient(const std::shared_ptr<Channel> &channel)
            : stub(proto::IoTService::NewStub(channel)) {}

    // Device
    bool CreateDevice(const util::types::Device &data) {
        // Request
        proto::Device device;
        // Set Request Data
        device.set_name(data.Name.toStdString());
        device.set_location(data.Location.toStdString());
        device.set_devicetype(static_cast<proto::DeviceType>(data.DeviceType));
        device.set_opcurl(data.OPCUrl.toStdString());
        device.set_ipaddress(data.IPAddress.toStdString());
        device.set_subnetmask(data.SubnetMask.toStdString());
        device.set_gateway(data.Gateway.toStdString());

        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncCreateDevice(&context, device, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool UpdateDevice(const util::types::Device &data) {
        // Request
        proto::Device device;
        // Set Request Data
        device.set_id(data.ID);
        device.set_name(data.Name.toStdString());
        device.set_location(data.Location.toStdString());
        device.set_devicetype(static_cast<proto::DeviceType>(data.DeviceType));
        device.set_opcurl(data.OPCUrl.toStdString());
        device.set_ipaddress(data.IPAddress.toStdString());
        device.set_subnetmask(data.SubnetMask.toStdString());
        device.set_gateway(data.Gateway.toStdString());

        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncUpdateDevice(&context, device, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool DeleteDevice(const int &deviceID) {
        // Request
        proto::Device device;
        // Set Request Data
        device.set_id(deviceID);
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncDeleteDevice(&context, device, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    util::types::Device GetDevice(const int &DeviceID) {
        // Device
        util::types::Device device;
        // Request
        proto::Device request;
        // Set Request Data
        request.set_id(DeviceID);
        // Response the state of request (user-defined-message)
        proto::Device response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Device> > rpc(
                stub->PrepareAsyncGetDevice(&context, request, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Return values
        if (status.ok()) {
            device.ID = int(response.id());
            device.Name = response.name().c_str();
            device.Location = response.location().c_str();
            device.DeviceType = static_cast<util::types::DeviceType>(response.devicetype());
            device.OPCUrl = response.opcurl().c_str();
            device.IPAddress = response.ipaddress().c_str();
            device.SubnetMask = response.subnetmask().c_str();
            device.Gateway = response.gateway().c_str();
            return device;
        } else {
            return device;
        }
    }

    QList<util::types::Device> GetDevices() {
        // Devices
        QList<util::types::Device> devices;
        // response
        proto::Device device;
        // Request
        proto::Empty request;
        // Set Request Data

        // Response the state of request (user-defined-message)
        proto::Device response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientReader<proto::Device> > rpc(
                stub->GetDevices(&context, request)
        );
        // Start RPC "CALL"
        while (rpc->Read(&device)) {
            util::types::Device tmp;

            tmp.ID = int(device.id());
            tmp.Name = device.name().c_str();
            tmp.Location = device.location().c_str();
            tmp.DeviceType = static_cast<util::types::DeviceType>(device.devicetype());
            tmp.OPCUrl = device.opcurl().c_str();
            tmp.IPAddress = device.ipaddress().c_str();
            tmp.SubnetMask = device.subnetmask().c_str();
            tmp.Gateway = device.gateway().c_str();

            devices.push_back(tmp);
        }
        // Get Status from the request-response
        status = rpc->Finish();

        // Return values
        if (status.ok())
            return devices;

        return {};
    }

    // Sensor
    bool CreateSensor(const util::types::Sensor &data) {
        // Request
        proto::Sensor sensor;
        // Set Request Data
        sensor.set_deviceid(data.DeviceID);
        sensor.set_id(data.ID);
        sensor.set_name(data.Name.toStdString());
        sensor.set_datatype(static_cast<proto::SensorDataType>(data.SensorDataType));
        sensor.set_gpionum(data.GPIONum);
        sensor.set_gpiotype(static_cast<proto::GPIOType>(data.GPIOType));
        sensor.set_pullupresistor(data.PullUpResistor);
        sensor.set_plcdataarea(static_cast<proto::PLCDataArea>(data.PLCDataArea));
        sensor.set_dataoffset(data.DataOffset);
        sensor.set_boolindex(data.BoolIndex);
        sensor.set_dbnum(data.DbNum);
        sensor.set_nodeid(data.NodeID.toStdString());

        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncCreateSensor(&context, sensor, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool DeleteSensor(const int &SensorID) {
        // Request
        proto::Sensor sensor;
        // Set Request Data
        sensor.set_id(SensorID);
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncDeleteSensor(&context, sensor, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool UpdateSensor(const util::types::Sensor &data) {
        // Request
        proto::Sensor sensor;
        // Set Request Data
        sensor.set_deviceid(data.DeviceID);
        sensor.set_id(data.ID);
        sensor.set_name(data.Name.toStdString());
        sensor.set_datatype(static_cast<proto::SensorDataType>(data.SensorDataType));
        sensor.set_gpionum(data.GPIONum);
        sensor.set_gpiotype(static_cast<proto::GPIOType>(data.GPIOType));
        sensor.set_pullupresistor(data.PullUpResistor);
        sensor.set_plcdataarea(static_cast<proto::PLCDataArea>(data.PLCDataArea));
        sensor.set_dataoffset(data.DataOffset);
        sensor.set_boolindex(data.BoolIndex);
        sensor.set_dbnum(data.DbNum);
        sensor.set_nodeid(data.NodeID.toStdString());

        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncUpdateSensor(&context, sensor, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    util::types::Sensor GetSensor(const int &SensorID) {
        // Sensor
        util::types::Sensor sensor;
        // Request
        proto::Sensor request;
        // Set Request Data
        request.set_id(SensorID);
        // Response the state of request (user-defined-message)
        proto::Sensor response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Sensor> > rpc(
                stub->PrepareAsyncGetSensor(&context, request, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Return values
        if (status.ok()) {
            sensor.ID = int(response.id());
            sensor.DeviceID = int(response.deviceid());
            sensor.Name = response.name().c_str();
            sensor.SensorDataType = static_cast<util::types::SensorDataType>(response.datatype());
            sensor.GPIONum = response.gpionum();
            sensor.GPIOType = static_cast<util::types::GPIOType>(response.gpiotype());
            sensor.PullUpResistor = response.pullupresistor();
            sensor.PLCDataArea = static_cast<util::types::PLCDataArea>(response.plcdataarea());
            sensor.DataOffset = response.dataoffset();
            sensor.BoolIndex = response.boolindex();
            sensor.DbNum = response.dbnum();
            sensor.NodeID = response.nodeid().c_str();

            return sensor;
        }

        return {};
    }

    QList<util::types::Sensor> GetSensors(const int &DeviceID) {
        // Sensors
        QList<util::types::Sensor> sensors;
        // Request
        proto::Device request;
        // Set Request Data
        request.set_id(DeviceID);
        // Response the state of request (user-defined-message)
        proto::Sensor response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientReader<proto::Sensor> > rpc(
                stub->GetSensors(&context, request)
        );
        // Start RPC "CALL"
        while (rpc->Read(&response)) {
            util::types::Sensor tmp;
            tmp.ID = int(response.id());
            tmp.DeviceID = int(response.deviceid());
            tmp.Name = response.name().c_str();
            tmp.SensorDataType = static_cast<util::types::SensorDataType>(response.datatype());
            tmp.GPIONum = response.gpionum();
            tmp.GPIOType = static_cast<util::types::GPIOType>(response.gpiotype());
            tmp.PullUpResistor = response.pullupresistor();
            tmp.PLCDataArea = static_cast<util::types::PLCDataArea>(response.plcdataarea());
            tmp.DataOffset = response.dataoffset();
            tmp.BoolIndex = response.boolindex();
            tmp.DbNum = response.dbnum();
            tmp.NodeID = response.nodeid().c_str();

            sensors.push_back(tmp);
        }
        // Get Status from the request-response
        status = rpc->Finish();

        // Return values
        if (status.ok())
            return sensors;

        return {};
    }

    // Record
    bool CreateRecord(const util::types::Record &data) {
        // Request
        proto::Record record;
        // Set Request Data
        record.set_deviceid(data.DeviceID);
        record.set_name(data.Name.toStdString());
        record.set_running(data.Running);
        for (const auto &recordSensor : data.RecordSensor) {
            auto n = record.mutable_recordsensor()->Add();
            n->set_sensorid(recordSensor.SensorID);
            n->set_recordtype(static_cast<proto::RecordType>(recordSensor.RecordType));
            n->set_triggervaluemin(recordSensor.TriggerValueMin.toStdString());
            n->set_triggervaluemax(recordSensor.TriggerValueMax.toStdString());
            n->set_interval(recordSensor.Interval);
        }
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncCreateRecord(&context, record, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool UpdateRecord(const util::types::Record &data) {
        // Request
        proto::Record record;
        // Set Request Data
        record.set_id(data.ID);
        record.set_deviceid(data.DeviceID);
        record.set_name(data.Name.toStdString());
        record.set_running(data.Running);
        for (const auto &recordSensor : data.RecordSensor) {
            auto n = record.mutable_recordsensor()->Add();
            n->set_sensorid(recordSensor.SensorID);
            n->set_recordtype(static_cast<proto::RecordType>(recordSensor.RecordType));
            n->set_triggervaluemin(recordSensor.TriggerValueMin.toStdString());
            n->set_triggervaluemax(recordSensor.TriggerValueMax.toStdString());
            n->set_interval(recordSensor.Interval);
        }
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncUpdateRecord(&context, record, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool DeleteRecord(const int &RecordID) {
        // Request
        proto::Record record;
        // Set Request Data
        record.set_id(RecordID);
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncDeleteRecord(&context, record, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    util::types::Record GetRecord(const int &RecordID) {
        // Record
        util::types::Record record;
        // Request
        proto::Record request;
        // Set Request Data
        request.set_id(RecordID);
        // Response the state of request (user-defined-message)
        proto::Record response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Record> > rpc(
                stub->PrepareAsyncGetRecord(&context, request, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Return values
        if (status.ok()) {

            record.ID = int(response.id());
            record.DeviceID = int(response.deviceid());
            record.Name = response.name().c_str();
            record.Running = response.running();
            for (const auto &recordSensor : response.recordsensor()) {
                util::types::RecordSensor tmp;
                tmp.SensorID = int(recordSensor.sensorid());
                tmp.RecordType = static_cast<util::types::RecordType>(recordSensor.recordtype());
                tmp.TriggerValueMin = recordSensor.triggervaluemin().c_str();
                tmp.TriggerValueMax = recordSensor.triggervaluemax().c_str();
                tmp.Interval = recordSensor.interval();

                record.RecordSensor.push_back(tmp);
            }

            return record;
        }

        return {};
    }

    QList<util::types::Record> GetRecords(const int &DeviceID) {
        // Records
        QList<util::types::Record> records;
        // Request
        proto::Device request;
        // Set Request Data
        request.set_id(DeviceID);
        // Response the state of request (user-defined-message)
        proto::Record response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientReader<proto::Record> > rpc(
                stub->GetRecords(&context, request)
        );
        // Start RPC "CALL"
        while (rpc->Read(&response)) {
            util::types::Record tmp;
            tmp.ID = int(response.id());
            tmp.DeviceID = int(response.deviceid());
            tmp.Name = response.name().c_str();
            tmp.Running = response.running();
            for (const auto &recordSensor : response.recordsensor()) {
                util::types::RecordSensor s;
                s.SensorID = int(recordSensor.sensorid());
                s.RecordType = static_cast<util::types::RecordType>(recordSensor.recordtype());
                s.TriggerValueMin = recordSensor.triggervaluemin().c_str();
                s.TriggerValueMax = recordSensor.triggervaluemax().c_str();
                s.Interval = recordSensor.interval();

                tmp.RecordSensor.push_back(s);
            }

            records.push_back(tmp);
        }
        // Get Status from the request-response
        status = rpc->Finish();

        // Return values
        if (status.ok())
            return records;

        return {};
    }

    // RecordData
    bool CreateRecordData(const util::types::RecordData &data) {
        // Request
        proto::RecordData recordData;
        // Set Request Data
        recordData.set_id(data.ID);
        recordData.set_sensorid(data.SensorID);
        recordData.set_datatype(static_cast<proto::SensorDataType>(data.SensorDataType));
        recordData.set_value(data.Value.toStdString());
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncCreateRecordData(&context, recordData, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    bool DeleteRecordData(const util::types::RecordData &data) {
        // Request
        proto::RecordData recordData;
        // Set Request Data
        recordData.set_id(data.ID);
        recordData.set_sensorid(data.SensorID);
        // Response the state of request (user-defined-message)
        proto::Empty response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientAsyncResponseReader<proto::Empty> > rpc(
                stub->PrepareAsyncDeleteRecordData(&context, recordData, &queue)
        );
        // Start RPC "CALL"
        rpc->StartCall();
        // Get Status from the request-response
        rpc->Finish(&response, &status, (void *) 1);
        void *got_tag;
        bool ok = false;

        // Block util the next result is available in the completion queue.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the queue is shutting down.
        GPR_ASSERT(queue.Next(&got_tag, &ok));
        // Verify that the result from queue corresponds, by the tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // That the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (status.ok())
            return true;

        return false;
    }

    QList<util::types::RecordData> GetRecordData(const util::types::RecordDataFilter &filter) {
        // RecordData
        QList<util::types::RecordData> recordData;
        // Request
        proto::RecordDataFilter request;
        // Set Request Data
        request.set_id(filter.ID);
        request.set_sensorid(filter.SensorID);
        request.set_filtervalue(static_cast<proto::FilterValue>(filter.FilterValue));
        request.set_minvalue(filter.MinValue.toStdString());
        request.set_maxvalue(filter.MaxValue.toStdString());
        request.set_filtertime(static_cast<proto::FilterTime>(filter.FilterTime));
        // Response the state of request (user-defined-message)
        proto::RecordData response;
        // ClientContext
        ClientContext context;
        // Queue for async communication
        CompletionQueue queue;
        // Status storage from Server (OK,CANCELLED...)
        Status status;
        // RPC "CALL" Object
        std::unique_ptr<ClientReader<proto::RecordData> > rpc(
                stub->GetRecordData(&context, request)
        );
        // Start RPC "CALL"
        while (rpc->Read(&response)) {
            util::types::RecordData tmp;
            tmp.ID = int(response.id());
            tmp.SensorID = int(response.sensorid());
            tmp.Timestamp = google::protobuf::util::TimeUtil::TimestampToSeconds(response.timestamp());

            recordData.push_back(tmp);
        }
        // Get Status from the request-response
        status = rpc->Finish();

        // Return values
        if (status.ok())
            return recordData;

        return {};
    }

private:
    std::unique_ptr<proto::IoTService::Stub> stub;
};

#endif //GRPC_CLIENT_GRPCCLIENT_H
