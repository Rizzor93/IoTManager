#ifndef BASE_H
#define BASE_H

#include <QObject>
#include "Config/Config.h"
#include "../gRPCClient/grpcClient.h"

using namespace grpc;

class BaseClass : public QObject {
Q_OBJECT
public:
    BaseClass() = default;;
protected:
    gRPCClient *client{};

    void connectGRPC() {
        auto *config = Config::getInstance();
        client = new gRPCClient(
                grpc::CreateChannel(config->getHost().toStdString() + ":" +
                                    config->getPort().toStdString(),
                                    grpc::InsecureChannelCredentials()));
    }

signals:

    void changed();

};

#endif //BASE_H
