#include "RadarController.h"
#include <iostream>

using namespace std;

RadarController::RadarController() : gen(rand()) {

    comms.registerCallback(&RadarController::msgCallback, this);

    comms.subscribe(common::MessageID::CONTROL_REQUEST_SUM);

}

void RadarController::start() {

    comms.runInForeground();

}

void RadarController::msgCallback(void* thisClass, common::MessageID msgId, void* data, size_t size) {

    RadarController* controller = static_cast<RadarController*>(thisClass);

    switch (msgId)
    {
    case common::MessageID::CONTROL_REQUEST_SUM:
        controller->processMsg<controls::RequestSum>(data, size);
        break;
    
    default:
        break;
    }

}

template <typename T>
void RadarController::processMsg(const void* data, size_t size) {
    lock_guard<mutex> lock(_lock);

    auto msg = parseProtobuf<T>(data,size);
    if (msg) {
        processMsg(msg.value());
    } else {
        cout << "Received Invalid Message" << endl;
    }
}

void RadarController::processMsg(controls::RequestSum sumRequest) {
    cout << "Got Sum Request" << endl;
    cout << sumRequest.DebugString() << endl;

    std::uniform_int_distribution<> dis(0, sumRequest.random_max());

    int sum = 0;
    int randMax = dis(gen);
    for (int i = 1; i < randMax; i++) {

        sum += i;
    }

    controls::SumResponse resp;
    resp.set_sum(sum);
    comms.publish(common::MessageID::BACKEND_SUM_RESPONSE, resp);

}
