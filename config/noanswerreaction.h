#ifndef NOANSWERREACTION_H
#define NOANSWERREACTION_H

#include "answerreaction.h"
#include <QTime>

namespace botlib {
namespace config {
class NoAnswerReaction : public AnswerReaction
{
private:

public:
    NoAnswerReaction();
};
}
}

#endif // NOANSWERREACTION_H
