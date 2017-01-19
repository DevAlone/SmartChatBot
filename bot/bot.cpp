#include "bot.h"


namespace botlib {

Bot::Bot(QObject *parent)
{

}

Bot::Bot(std::unique_ptr<config::Config> config)
    : config(std::move(config))
{
    currentConfigMessage = config->rootMessage.get();
    if(currentConfigMessage)
        sendMessageToUser(currentConfigMessage->text);
}

QList<Message> &Bot::getMessageHistory()
{
    return messageHistory;
}

Message *Bot::getLastMessage()
{
    if(messageHistory.empty())
        return nullptr;
    return &messageHistory.last();
}

bool Bot::setConfigFromXml(const QString &xmlData)
{
    config::Config *config = config::Config::fromXml(xmlData);
    if(!config)
        return false;
    this->config.reset(config);
    messageHistory.clear();
    currentConfigMessage = config->rootMessage.get();
    sendMessageToUser(currentConfigMessage->text);
    return true;
}



void Bot::sendMessageToBot(const QString &text)
{
    if(!config)
        return;

    Message userMessage(botlib::Message::USER_MESSAGE, text);

    messageHistory.push_back(userMessage);

    QList<Message> changes({ userMessage });

    Message botMessage = getAnswer(userMessage);
    if(botMessage.message.length() > 0)
    {
        messageHistory.push_back(botMessage);
        changes.append(botMessage);
    }


    emit messageHistoryChanged(changes);
}


void Bot::sendMessageToUser(QString text)
{
    Message botMessage(Message::BOT_MESSAGE, text);
    messageHistory.push_back(botMessage);
    emit botAnswered(botMessage);
    emit messageHistoryChanged(QList<Message>({ botMessage }));
}

/* function to get bot answer depending on the current config */
Message Bot::getAnswer(Message userMessage)
{
    Message botAnswer(Message::BOT_MESSAGE, QString(""));


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
void Bot::update()
{
    if(!config)
        return;

    qDebug() << "bot updating...";
    Message *lastMessage = getLastMessage();
    if(!lastMessage)
        return;

    bool sent = false;
    if(lastMessage->type == Message::BOT_MESSAGE) {
        qDebug() << "last message sent by bot";
        for(int i = 0; i < currentConfigMessage->reactions.length() && !sent; i++) {
            config::Reaction *reaction = &currentConfigMessage->reactions[i];
            if(reaction->type == "no answer") {
                qDebug() << "found no answer reaction";

                QDateTime timeElapsed = lastMessage->sendingDateTime;
                timeElapsed  = timeElapsed.addSecs(reaction->time.second());
                qDebug() << "reaction time seconds is " << reaction->time.second();
                qDebug() << "lastMessage.sendingDateTime is " << lastMessage->sendingDateTime;
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
}




}
