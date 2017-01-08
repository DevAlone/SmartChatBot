#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

namespace BotLib {
    class Message;
}
class BotLib::Message
{
protected:

public:
    enum MessageType { USER_MESSAGE, BOT_MESSAGE };
    MessageType type;
    QString message;
    Message();
    Message(MessageType type, QString message);
    Message(int i);
};

#endif // MESSAGE_H
