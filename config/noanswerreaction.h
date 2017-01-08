#ifndef NOANSWERREACTION_H
#define NOANSWERREACTION_H

#include "answerreaction.h"
#include <QTime>

namespace BotConfig {
class NoAnswerReaction : public AnswerReaction
{
private:
    QTime time;
public:
    NoAnswerReaction();
};
}

#endif // NOANSWERREACTION_H
