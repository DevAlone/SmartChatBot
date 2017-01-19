#include "botmessage.h"
#include <QDebug>

namespace botlib { namespace config {

BotMessage::BotMessage()
{

}

BotMessage::BotMessage(QString text, QList<Reaction> reactions)
    : text(text), reactions(reactions)
{

}

BotMessage::~BotMessage()
{
//    for (int i = 0; i < reactions.length(); i++) {
//        delete reactions[i];
//    }
    qDebug() << "bot message destructor";
}

}}
