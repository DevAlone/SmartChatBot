#include "message.h"

namespace botlib
{
Message::Message(Message::MessageType type, QString message)
{
    this->type = type;
    this->message = message;
    this->sendingDateTime = QDateTime::currentDateTime();
}

}
