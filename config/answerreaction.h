#ifndef BOTCONFIGANSWERREACTION_H
#define BOTCONFIGANSWERREACTION_H

#include "reaction.h"

#include <QString>


namespace BotConfig {
class AnswerReaction : public Reaction
{
protected:
    QString userMessage;

public:
    AnswerReaction();
};
}


#endif // BOTCONFIGANSWERREACTION_H
