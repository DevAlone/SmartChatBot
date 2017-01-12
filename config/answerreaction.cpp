#include "answerreaction.h"

namespace botlib {
namespace config {
AnswerReaction::AnswerReaction()
{

}

AnswerReaction::AnswerReaction(QString userMessage, config::BotMessage *botMessage, config::BotAction *botAction)
    :Reaction("answer", botMessage, botAction), userMessage(userMessage)
{

}

}
}
