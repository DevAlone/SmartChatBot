#ifndef BOTCONFIG_H
#define BOTCONFIG_H

#include "botmessage.h"


namespace BotConfig {
    class Config
    {
    protected:
        BotMessage *rootMessage;
    public:
        Config();
    };
}


#endif // BOTCONFIG_H
