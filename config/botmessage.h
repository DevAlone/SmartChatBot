#ifndef BOTCONFIGMESSAGE_H
#define BOTCONFIGMESSAGE_H

#include "reaction.h"

#include <QList>
#include <QString>


namespace BotConfig {
class Reaction;

class BotMessage
{
private:
    QString text;
    QList<Reaction> reactions;
public:
    BotMessage();
};
}


#endif // BOTCONFIGMESSAGE_H
