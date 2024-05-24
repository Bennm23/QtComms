#ifndef ZERO_CLIENTQT_H
#define ZERO_CLIENTQT_H

#include "ZeroChannel.h"
#include <qt5/QtCore/QObject>


class ZeroClientQt : public QObject, public ZeroChannel {

    Q_OBJECT

    public:
        ZeroClientQt() : ZeroChannel() {
            qRegisterMetaType<common::MessageID>("common::MessageID");
            qRegisterMetaType<size_t>("size_t");
            // qRegisterMetaType<void*>("ProtoData");
        };
        virtual ~ZeroClientQt() {};

        void subscribe(common::MessageID id) {
            subs.insert(id);
        }

    Q_SIGNALS:
        void qCallback(common::MessageID msgId, void* data, size_t size);

    protected:
        void createSockets() {
            std::cout << "Creating QT CLient" << std::endl;
            pubSocket = std::make_shared<socket_t>(ctx, socket_type::pub);
            subSocket = std::make_shared<socket_t>(ctx, socket_type::sub);

            subSocket->set(sockopt::subscribe, "");
            subSocket->connect(BROKER_PUB_ADDR);

            pubSocket->connect(BROKER_SUB_ADDR);
        };

        void handleMsg(message_t &msgTopic, message_t &msgBody) {
            std::string topicStr(static_cast<char*>(msgTopic.data()), msgTopic.size());

            common::MessageID id;
            auto res = common::MessageID_Parse(topicStr, &id);

            if (!res) {
                std::cerr << "Failed to parse topicStr = " << topicStr << std::endl;
                return;
            }

            emit qCallback(id, msgBody.data(), msgBody.size());
        };

    private:

        std::set<common::MessageID> subs;
};

#endif
