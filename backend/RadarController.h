#ifndef RADAR_CONTROLLER_H
#define RADAR_CONTROLLER_H

#include "ZeroClient.h"
#include "common.pb.h"
#include "controls.pb.h"

#include <mutex>
#include <random>
#include <optional>

class RadarController {

    public:
        RadarController();

        void start();

    private:

        ZeroClient comms;
        std::mutex _lock;

        std::random_device rand;
        std::mt19937 gen;



        static void msgCallback(void* thisClass, common::MessageID msgId, void* data, size_t size);

        void handlePubSender(void* data, size_t size);

        template <typename T>
        void processMsg(const void* data, size_t size);

        void processMsg(controls::RequestSum);


        template <typename T>
        std::optional<T> parseProtobuf(const void* data, size_t size) {
            static_assert(std::is_base_of<google::protobuf::Message, T>::value, "T Must Extend Message");


            T message;
            if (message.ParseFromArray(data,size)) return message;
            else return std::nullopt;
        }
};

#endif