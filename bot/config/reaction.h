#ifndef BOTCONFIGREACTION_H
#define BOTCONFIGREACTION_H

//#include <QSharedPointer>
#include <memory>

#include "botaction.h"
#include "botmessage.h"

#include <QString>
#include <QTime>


namespace botlib {
namespace config {
class BotMessage;

class Reaction
{
protected:

public:
    QString type;
    std::shared_ptr<BotMessage> botMessage;
    //BotMessage *botMessage;
    //QSharedPointer<BotAction> botAction;
    BotAction botAction;
    //std::shared_ptr<BotAction> botAction;
    QString userMessage;
    QTime time;
    Reaction(QString type, std::shared_ptr<BotMessage> botMessage, BotAction botAction, QString userMessage, QTime time);
    ~Reaction();
};
}
}


#endif // BOTCONFIGREACTION_H
