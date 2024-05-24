#include "ControlWindow.h"
#include "./ui_ControlWindow.h"

#include <iostream>

using namespace std;

ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    connect(ui->startSendBtn, &QPushButton::pressed, this, &ControlWindow::handleSendButton);

    connect(&comms, &ZeroClientQt::qCallback, this, &ControlWindow::qMsgCallback);

    comms.subscribe(common::MessageID::BACKEND_SUM_RESPONSE);
    comms.runInBackground();

}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::handleSendButton(){
    cout << "Send Button Pressed" << endl;

    controls::RequestSum req;
    req.set_random_max(112);

    cout << "Sending Request Sum" << endl;
    comms.publish(common::CONTROL_REQUEST_SUM, req);

}

void ControlWindow::qMsgCallback(common::MessageID msgId, void* data, size_t size) {

    switch (msgId)
    {
    case common::MessageID::BACKEND_SUM_RESPONSE:
        handleSumResponse(data, size);
        break;
    
    default:
        break;
    }

}

void ControlWindow::handleSumResponse(void* data, size_t size) {
    std::cout << "Got Sum Response" << std::endl;
    auto resp = parseProtobuf<controls::SumResponse>(data, size);

    if (!resp.has_value()) {
        std::cout << "Invalid Sum Response Received" << std::endl;
    }

    std::cout << resp->DebugString() << endl;

    ui->sendingLabel->setText(QString("GOT A MESSAGE"));
}
