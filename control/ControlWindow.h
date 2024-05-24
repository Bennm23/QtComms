#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <optional>
#include <QMainWindow>

#include "ZeroClientQt.h"
#include "controls.pb.h"
#include "common.pb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

private:
    Ui::ControlWindow *ui;
    ZeroClientQt comms;

    void handleSumResponse(void* data, size_t size);
    template <typename T>
    std::optional<T> parseProtobuf(const void* data, size_t size) {
        static_assert(std::is_base_of<google::protobuf::Message, T>::value, "T Must Extend Message");


        T message;
        if (message.ParseFromArray(data,size)) return message;
        else return std::nullopt;
    }

private Q_SLOTS:
    void handleSendButton();
    void qMsgCallback(common::MessageID msgId, void* data, size_t size);

};
#endif // CONTROLWINDOW_H
