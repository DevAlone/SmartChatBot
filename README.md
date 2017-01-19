# SmartBot

## Chat bot on Qt. 

Bot classes located in bot/ 
To create Bot you can create an object of Bot class and set config:

```
#include "bot/bot.h"

...

Bot *bot = new botlib::Bot;

QFile file("config.xml");
file.open(QFile::ReadOnly);
if(!file.isOpen()) {
// open file error
}
QString xmlData = file.readAll();

file.close();

if(!bot->setConfigFromXml(xmlData)) {
// parsing error
}

```

For communication with bot you have to use "void sendMessageToBot(const QString & text);" method and signals, for example, "messageHistoryChanged(const QList<botlib::Message> &);"

```
connect(bot, SIGNAL(messageHistoryChanged(QList<botlib::Message>)),
            this, SLOT(messageHistoryChanged(QList<botlib::Message>)));

...

QString text = "hi, bot!";
bot->sendMessageToBot(text);
```
