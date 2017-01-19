#-------------------------------------------------
#
# Project created by QtCreator 2017-01-19T21:08:28
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartBot5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bot/config/botaction.cpp \
    bot/config/botconfig.cpp \
    bot/config/botmessage.cpp \
    bot/config/reaction.cpp \
    bot/bot.cpp \
    bot/message.cpp

HEADERS  += mainwindow.h \
    bot/config/botaction.h \
    bot/config/botconfig.h \
    bot/config/botmessage.h \
    bot/config/reaction.h \
    bot/bot.h \
    bot/message.h

FORMS    += mainwindow.ui

CONFIG += c++14
