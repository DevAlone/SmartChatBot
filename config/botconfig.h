#ifndef BOTCONFIG_H
#define BOTCONFIG_H

#include <memory>
#include "botmessage.h"

#include <QFile>


namespace botlib {
namespace config {
class Config
{
private:
    //Config(Config & config) {}
   // Config & operator=(Config &config) {}
protected:

public:
    //std::auto_ptr<BotMessage> rootMessage;
    std::unique_ptr<BotMessage> rootMessage;
    //BotMessage *rootMessage;
    //Config(std::shared_ptr<BotMessage> rootMessage);
    Config(BotMessage *rootMessage);
    ~Config();
    static Config* fromXml(QString xmlData);
};
}
}


#endif // BOTCONFIG_H
