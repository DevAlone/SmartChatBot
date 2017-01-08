#include "bot.h"
#include "bot/message.h"


using namespace BotLib;

Message Bot::getAnswer(Message userMessage)
{
    // function to get bot answer depending on the current config

    return Message(BotLib::Message::BOT_MESSAGE, QString("bot answer"));
}

Bot::Bot(BotConfig::Config config)
{

}

Bot::Bot()
{

}

QList<Message> &Bot::getMessageHistory()
{
    return messageHistory;

}

Message Bot::getLastMessage()
{
    return messageHistory.last();
}

Message Bot::sendMessage(QString text)
{
    Message userMessage(BotLib::Message::USER_MESSAGE, text);
    //userMessage.message = text;

    messageHistory.push_back(userMessage);

    Message botMessage = getAnswer(userMessage);
    messageHistory.push_back(botMessage);

    return botMessage;
}
