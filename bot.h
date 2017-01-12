#ifndef BOT_H
#define BOT_H

#include "message.h"
#include "config/answerreaction.h"
#include "config/botaction.h"
#include "config/botconfig.h"
#include "config/botmessage.h"
#include "config/noanswerreaction.h"
#include "config/reaction.h"

#include <bot/config/botconfig.h>

namespace botlib {
class Bot
{
protected:
    config::Config* config;
    //std::auto_ptr<config::BotMessage> currentConfigMessage;
    config::BotMessage* currentConfigMessage;
    QList<Message> messageHistory;
    Message getAnswer(Message userMessage);
public:
    Bot(config::Config* config);
    Bot();

    QList<Message>& getMessageHistory();
    Message& getLastMessage();

    Message sendMessageToBot(QString text);
    bool update();
private:
    void sendMessageToUser(QString text);
};
}

#endif // BOT_H

