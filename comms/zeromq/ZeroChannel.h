#ifndef ZERO_CHANNEL_H
#define ZERO_CHANNEL_H

#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <google/protobuf/message.h>
#include "common.pb.h"

using namespace zmq;
using namespace std;

class ZeroChannel {
    public:

        ZeroChannel() : ctx(2) {};
        ~ZeroChannel() {

            ctx.shutdown();
            ctx.close();
        };

        void runInForeground(){
            createSockets();
            std::cout << "Starting Channel" << std::endl;

            while(true) {
                receiveMsg();
            }
        };
        void runInBackground(){
            createSockets();
            std::thread receiver([this]() {
                std::cout << "Running in background" << std::endl;
                while(true) {
                    receiveMsg();
                }
            });
            receiver.detach();
        };

        void publish(const common::MessageID id, const google::protobuf::Message &msg) {
            std::string topic = common::MessageID_Name(id);
            message_t msgTopic(topic.size());
            memcpy(msgTopic.data(), topic.data(), topic.size());

            std::string serializedMsg = msg.SerializeAsString();
            message_t msgBody(serializedMsg.size());
            memcpy(msgBody.data(), serializedMsg.data(), serializedMsg.size());

            pubSocket->send(msgTopic, send_flags::sndmore);
            pubSocket->send(msgBody, send_flags::none);
        };

    protected:
        const std::string BROKER_SUB_ADDR = "tcp://127.0.0.1:1241";
        const std::string BROKER_PUB_ADDR = "tcp://127.0.0.1:1242";
        context_t ctx;
        std::shared_ptr<socket_t> pubSocket = nullptr;
        std::shared_ptr<socket_t> subSocket = nullptr;

        virtual void handleMsg(message_t &msgTopic, message_t &msgBody) {
            pubSocket->send(msgTopic, send_flags::sndmore);
            pubSocket->send(msgBody, send_flags::none);
        };

        virtual void createSockets() {
            std::cout << "Creating Broker" << std::endl;
            pubSocket = std::make_shared<socket_t>(ctx, socket_type::pub);
            subSocket = std::make_shared<socket_t>(ctx, socket_type::sub);

            subSocket->bind(BROKER_SUB_ADDR);
            subSocket->set(sockopt::subscribe, "");

            pubSocket->bind(BROKER_PUB_ADDR);

        };

    private:
        void receiveMsg() {
            message_t msgTopic;
            auto res = subSocket->recv(msgTopic);

            if (!res.has_value()) {
                std::cerr << "Failed To Receive" << std::endl;
                return;
            } else if (res.value() <= 0) {
                std::cerr << "Read Bad Bytes" << std::endl;
                return;
            }

            bool hasMore = subSocket->get(sockopt::rcvmore);

            if (!hasMore)
            {
                std::cerr << "Got ZMsg without topic or body, abort" << std::endl;
                return;
            }

            message_t msgBody;
            res = subSocket->recv(msgBody);

            if (!res.has_value()) {
                std::cerr << "Failed To Receive" << std::endl;
                return;
            } else if (res.value() <= 0) {
                std::cerr << "Read Bad Bytes" << std::endl;
                return;
            }
            
            handleMsg(msgTopic, msgBody);
        };
};

#endif
