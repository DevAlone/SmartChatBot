#ifndef BOT_H
#define BOT_H

#include "message.h"

#include <bot/config/botconfig.h>

namespace BotLib {
    class Bot;
}

class BotLib::Bot
{
protected:
    BotConfig::Config config;
    QList<Message> messageHistory;
    Message getAnswer(Message userMessage);
public:
    Bot(BotConfig::Config config);
    Bot();

    QList<Message>& getMessageHistory();
    Message getLastMessage();

    Message sendMessage(QString text);
};

#endif // BOT_H

