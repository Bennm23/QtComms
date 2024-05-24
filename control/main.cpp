#include <iostream>
#include "ZeroChannel.h"
#include "ZeroClient.h"
#include "controls.pb.h"
#include "common.pb.h"

#include <QApplication>
#include "ControlWindow.h"

using namespace std;


// class Client1 {
//     public:
//         Client1() {
//             comms.registerCallback(&Client1::msgCallback, this);
//             comms.subscribe(common::MessageID::PUB_SENDER);
//             comms.runInBackground();
//         }

//     private:
//         ZeroClient comms;

//         static void msgCallback(void* thisClass, common::MessageID id, void* data, size_t size) {
//             cout << "In Msg Callback" << std::endl;
//             Client1* client = static_cast<Client1*>(thisClass);

//             switch (id)
//             {
//             case common::MessageID::PUB_SENDER:
//                 client->handlePubSender(data, size);
//                 break;
            
//             default:
//                 cout << "Received Unrecognized Msg ID = " << common::MessageID_Name(id) << endl;
//                 break;
//             }
//         }

//         void handlePubSender(void* data, size_t size) {
//             cout << "Got Pub Sender" << endl;

//             controls::PublishMessage pubMsg;
//             pubMsg.ParseFromArray(data, size);

//             cout << pubMsg.DebugString() << endl;


//             controls::ResponseMessage resp;
//             resp.set_response("Hello Sender");

//             comms.publish(common::MessageID::PUB_RESPONSE, resp);
//         }
// };

// void cb2(void*, common::MessageID id, void* data, size_t size) {
//     controls::ResponseMessage resp;
//     resp.ParseFromArray(data, size);

//     cout << "Got Response Message" << endl;
//     cout << resp.DebugString() << endl;

// }

int main(int argc, char *argv[]) {
    // std::cout << "In Main" << std::endl;

    // controls::PublishMessage pubMsg;

    // ZeroClient client;
    // client.registerCallback(cb2);
    // client.subscribe(common::MessageID::PUB_RESPONSE);
    // client.runInBackground();

    // Client1 c;

    // ZeroChannel zc;
    // zc.runInBackground();

    // for (int i = 0; i < 5; i++) {
    //     pubMsg.set_sum(i);
        
    //     client.publish(common::MessageID::PUB_SENDER, pubMsg);
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    QApplication app(argc, argv);
    ControlWindow w;
    w.show();
    return app.exec();

}