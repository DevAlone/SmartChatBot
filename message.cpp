#include "message.h"
using namespace BotLib;

Message::Message()
{

}

Message::Message(Message::MessageType type, QString message)
{
    this->type = type;
    this->message = message;
}

Message::Message(int i)
{


}

