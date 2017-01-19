#ifndef BOT_H
#define BOT_H

#include <memory>
#include <QObject>
#include <QDebug>

#include "message.h"
#include "config/botconfig.h"




namespace botlib {

class Bot : public QObject
{
    Q_OBJECT

public:
    explicit Bot(QObject *parent = 0);
    Bot(std::unique_ptr<config::Config> config);

    QList<Message> & getMessageHistory();
    Message *getLastMessage();
    bool setConfigFromXml(const QString &xmlData);


signals:
    void botAnswered(const Message & message);
    void messageHistoryChanged(const QList<botlib::Message> &);
public slots:
    void sendMessageToBot(const QString & text);
    void update();

protected:
    std::unique_ptr<config::Config> config;
    config::BotMessage* currentConfigMessage;
    QList<Message> messageHistory;
    Message getAnswer(Message userMessage);

private:
    void sendMessageToUser(QString text);

};

}
#endif // BOT_H
