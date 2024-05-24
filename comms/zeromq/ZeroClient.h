#ifndef ZERO_CLIENT_H
#define ZERO_CLIENT_H

#include "ZeroChannel.h"

using namespace zmq;

//instance, id, data, size
typedef void (*MsgCallback)(void*, common::MessageID, void*, size_t);

class ZeroClient : public ZeroChannel {

    public:
        ZeroClient() : ZeroChannel() {};

        ~ZeroClient(){};

        void registerCallback(MsgCallback cb, void* thisClass = nullptr) {
            callback = cb;
            callbackClass = thisClass;

        }
        void subscribe(common::MessageID id) {
            subscriptions.insert(id);
        }

    protected:
        void createSockets() {
            std::cout << "Creating CLient" << std::endl;
            pubSocket = std::make_shared<socket_t>(ctx, socket_type::pub);
            subSocket = std::make_shared<socket_t>(ctx, socket_type::sub);

            subSocket->set(sockopt::subscribe, "");
            subSocket->connect(BROKER_PUB_ADDR);

            pubSocket->connect(BROKER_SUB_ADDR);
        };

        virtual void handleMsg(message_t &msgTopic, message_t &msgBody) {
            std::string topicStr(static_cast<char*>(msgTopic.data()), msgTopic.size());

            common::MessageID id;
            auto res = common::MessageID_Parse(topicStr, &id);

            if (!res) {
                std::cerr << "Failed to parse topicStr = " << topicStr << std::endl;
                return;
            }

            auto it = subscriptions.find(id);

            if (it == subscriptions.end()) return;

            if (!callback) return;

            callback(callbackClass, id, msgBody.data(), msgBody.size());
        };

    private:
        std::set<common::MessageID> subscriptions;
        MsgCallback callback = NULL;
        void* callbackClass = nullptr;
};

#endif
