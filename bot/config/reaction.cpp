#include "reaction.h"
#include <QDebug>

namespace botlib { namespace config {
//Reaction::Reaction() : botMessage(0), botAction(0)
//{

//}

//Reaction::Reaction(QString type, config::BotMessage *botMessage, config::BotAction *botAction)
//    : type(type), botMessage(botMessage), botAction(botAction)
//{

//}

Reaction::Reaction(QString type, std::shared_ptr<BotMessage> botMessage, BotAction botAction, QString userMessage, QTime time)
    : type(type), botMessage(botMessage), botAction(botAction), userMessage(userMessage), time(time)
{

}

Reaction::~Reaction()
{
    //delete botAction;
    //delete botMessage;
    qDebug() << "reaction destructor!";
    //delete botAction;
    //delete botMessage;
    //delete botAction;
}

}}
