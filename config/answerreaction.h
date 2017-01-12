#ifndef BOTCONFIGANSWERREACTION_H
#define BOTCONFIGANSWERREACTION_H

#include "reaction.h"

#include <QString>

namespace botlib {
namespace config {
class AnswerReaction : public config::Reaction
{
protected:


public:

    AnswerReaction();
    AnswerReaction(QString userMessage, BotMessage *botMessage, BotAction *botAction);
};
}
}

#endif // BOTCONFIGANSWERREACTION_H
