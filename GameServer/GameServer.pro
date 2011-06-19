#-------------------------------------------------
#
# Project created by QtCreator 2011-05-30T22:44:05
#
#-------------------------------------------------

QT       += core gui\
            network\
            sql

TARGET = GameServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainserver.cpp \
    abstractgameserver.cpp \
    gameserverfactory.cpp \
    httpserver.cpp \
    thousandgameserverfactory.cpp \
    connectionmanager.cpp \
    thousandgameserver.cpp \
    gamethousand.cpp \
    abstractqueryhandler.cpp \
    thousandgamequeryhandler.cpp \
    abstractdataparser.cpp \
    thousandgamedataparser.cpp \
    config.cpp

HEADERS  += mainwindow.h \
    mainserver.h \
    abstractgameserver.h \
    config.h \
    description.h \
    gameserverfactory.h \
    httpserver.h \
    thousandgameserverfactory.h \
    connectionmanager.h \
    thousandgameserver.h \
    gamethousand.h \
    protocol.h \
    abstractqueryhandler.h \
    thousandgamequeryhandler.h \
    abstractdataparser.h \
    thousandgamedataparser.h \
    card.h

OTHER_FILES += \
    ProtocolDescription.txt
