#ifndef BOTCONFIGREACTION_H
#define BOTCONFIGREACTION_H

#include "botaction.h"
#include "botmessage.h"

#include <QString>


namespace BotConfig {
class BotMessage;

class Reaction
{
protected:
    QString type;
    BotConfig::BotMessage *botMessage;
    BotAction *botAction;
public:
    Reaction();
};
}


#endif // BOTCONFIGREACTION_H
