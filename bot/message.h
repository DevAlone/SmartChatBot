#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDate>
#include <QString>

namespace botlib {
class Message
{
protected:

public:
    enum MessageType { USER_MESSAGE, BOT_MESSAGE };
    QDateTime sendingDateTime ;
    MessageType type;
    QString message;
    Message(MessageType type, QString message);
};
}

#endif // MESSAGE_H
