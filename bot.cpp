#include "bot.h"
#include "bot/message.h"
#include "config/reaction.h"
#include <QMessageBox>
#include <QDebug>


namespace botlib
{

Message Bot::getAnswer(Message userMessage)
{
    Message botAnswer(Message::BOT_MESSAGE, QString(""));

    // function to get bot answer depending on the current config
//    if(!currentConfigMessage)
//        currentConfigMessage = config->rootMessage;
    bool sent = false;
    for(int i=0;i<currentConfigMessage->reactions.length() && !sent;i++)
    {
        config::Reaction *reaction = &currentConfigMessage->reactions[i];
        if(reaction->type == "answer")
        {
            if(reaction->userMessage == ""
                    || reaction->userMessage == userMessage.message)
            {
                // send message
                if(reaction->botMessage)
                {
                    botAnswer.message = reaction->botMessage->text;
                    if(!reaction->botMessage->reactions.empty())
                        currentConfigMessage = reaction->botMessage.get();
                    sent = true;        // чтоб эта итерация была последней
                }
                // do action
                if(reaction->botAction.action.length() > 0)
                {

                }
            }
        }
    }

    return botAnswer;
}

Bot::Bot(config::Config *config)
    : config(config)
{
    currentConfigMessage = config->rootMessage.get();
    if(currentConfigMessage)
    {
        Message botMessage(botlib::Message::BOT_MESSAGE, currentConfigMessage->text);
        messageHistory.push_back(botMessage);
    }
}

Bot::Bot()
{
    throw 1;
}

QList<Message> &Bot::getMessageHistory()
{
    return messageHistory;

}

Message& Bot::getLastMessage()
{
    return messageHistory.last();
}

Message Bot::sendMessageToBot(QString text)
{
    Message userMessage(botlib::Message::USER_MESSAGE, text);

    messageHistory.push_back(userMessage);

    Message botMessage = getAnswer(userMessage);
    if(botMessage.message.length() > 0)
        messageHistory.push_back(botMessage);

    return botMessage;
}

void Bot::sendMessageToUser(QString text)
{
    Message botMessage(Message::BOT_MESSAGE, text);
    messageHistory.push_back(botMessage);
}

bool Bot::update()
{
    qDebug() << "bot updating...";
    Message &lastMessage = getLastMessage();
    bool sent = false;
    for(int i=0;i<currentConfigMessage->reactions.length() && !sent;i++)
    {
        config::Reaction *reaction = &currentConfigMessage->reactions[i];
        if(reaction->type == "no answer")
        {
            qDebug() << "found no answer reaction";
            if(lastMessage.type == Message::BOT_MESSAGE) {
                qDebug() << "last message sent by bot";
                QDateTime timeElapsed = lastMessage.sendingDateTime;
                timeElapsed  = timeElapsed.addSecs(reaction->time.second());
                qDebug() << "reaction time seconds is " << reaction->time.second();
                qDebug() << "lastMessage.sendingDateTime is " << lastMessage.sendingDateTime;
                qDebug() << "time elapsed " << timeElapsed;
                qDebug() << "current time is " << QDateTime::currentDateTime();
                if(QDateTime::currentDateTime() >= timeElapsed) {

                    if(reaction->botMessage) {
                        qDebug() << "message sended";

                        sendMessageToUser(reaction->botMessage->text);

                        if(!reaction->botMessage->reactions.empty())
                            currentConfigMessage = reaction->botMessage.get();
                        sent = true;
                    }
                    if(reaction->botAction.action.length() > 0) {
                        // do something
                    }
                }
            }
        }
    }
    return sent;
}

}
