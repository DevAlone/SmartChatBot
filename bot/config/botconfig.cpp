#include "botconfig.h"
#include <QtXml>
#include <QMessageBox>
#include <QDebug>

namespace botlib { namespace config {

//Config::Config(std::shared_ptr<BotMessage> rootMessage)
//    : rootMessage(rootMessage)
//{
//    //this->rootMessage = new std::auto_ptr<BotMessage>(rootMessage);
//    //this->rootMessage = rootMessage;
//}

Config::Config(BotMessage *rootMessage)
    : rootMessage(rootMessage)
{

}

Config::~Config()
{

}


namespace xmlparser {
BotMessage* rootMessage;
Reaction processReaction(const QDomElement &reactionNode);

BotMessage* processBotMessage(const QDomElement &botMessageNode)
{
    // process tags in bot message like "text" or "reactions"

    BotMessage *botMessage = new BotMessage();

    QDomNode domNode = botMessageNode.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                QString tagName = domElement.tagName();
                if(tagName == "text") {
                    botMessage->text = domElement.text();
                } else if (tagName == "reactions") {
                    botMessage->reactions.push_back(processReaction(domElement));
                }
            }
        }
        domNode = domNode.nextSibling();
    }
    return botMessage;
}

Reaction processReaction(const QDomElement &reactionNode)
{
    qDebug() << "start processing reactions...";
    // process tags in reaction, for example "usermessage", "botmessage", etc

    QString reaction_type;
    //QString bot_message;
    //BotAction bot_action;
    QString reaction_userMessage;
    QTime reaction_time;
    BotMessage *reaction_botMessage = 0;
    BotAction reaction_BotAction;

    reaction_type = reactionNode.attribute("type");

    QDomNode domNode = reactionNode.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                QString tagName = domElement.tagName();
                qDebug() << "tagName = " << tagName;
                if(tagName == "usermessage") {
                    reaction_userMessage = domElement.text();
                } else if(tagName == "time") {
                    bool isOk = false;
                    int seconds = domElement.text().toInt(&isOk);
                    if(isOk)
                        reaction_time = QTime(0, 0, seconds);
                    qDebug() << "isOk = " << isOk <<
                                "seconds = " << seconds;
                } else if (tagName == "botmessage") {
                    reaction_botMessage = processBotMessage(domElement);
                }
            }
        }
        domNode = domNode.nextSibling();
    }
    return Reaction(reaction_type,
                        std::shared_ptr<BotMessage>(reaction_botMessage),
                        reaction_BotAction,
                        reaction_userMessage,
                        reaction_time);
}

}

Config *Config::fromXml(QString xmlData)
{
qDebug() << "start parsing";
// parse xml
    QDomDocument domDoc;
    if(domDoc.setContent(xmlData))
    {
        QDomElement domElement = domDoc.documentElement();
        if(!domElement.isNull()) {
            if(domElement.tagName() == "botmessage") {
                xmlparser::rootMessage = xmlparser::processBotMessage(domElement);
            }
            else
                qDebug() << "botmessage is missing";
        } else
            qDebug() << "invalid xml document";
        //xmlparser::rootMessage = new BotMessage();
        //xmlParserBotMessageP = xmlParserRootMessage;
        //xmlparser::traverseNode(domElement);

    } else {
        qDebug() << "invalid xml document setContent";
        qDebug() << "xmlData: " << xmlData;
    }
    qDebug() << (xmlparser::rootMessage ? "parsed ok" : "parsed error");
    if(xmlparser::rootMessage)
        return new Config(xmlparser::rootMessage);
    return 0;
}

}}
