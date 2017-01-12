#ifndef BOTCONFIGMESSAGE_H
#define BOTCONFIGMESSAGE_H

#include "reaction.h"

#include <QList>
#include <QString>


namespace botlib {
namespace config {
class Reaction;

class BotMessage
{
private:
public:

    QString text;
    QList<Reaction> reactions;

    BotMessage();
    BotMessage(QString text, QList<Reaction> reactions);
    ~BotMessage();
};
}
}


#endif // BOTCONFIGMESSAGE_H
