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

TRANSLATIONS += translations/lang_en_EN.ts \
                translations/lang_ru_RU.ts

INCLUDEPATH += \
               Game1000\
               HTTPServer

DEPENDPATH += \
               Game1000\
               HTTPServer

RC_FILE = GameServer.rc

SOURCES += \
    main.cpp\
    mainserver.cpp \
    abstractgameserver.cpp \
    gameserverfactory.cpp \
    thousandgameserverfactory.cpp \
    connectionmanager.cpp \
    thousandgameserver.cpp \
    abstractqueryhandler.cpp \
    abstractdataparser.cpp \
    config.cpp \
    tablemodel.cpp \
    Game1000/thousandgamedataparser.cpp \
    Game1000/gamethousand.cpp \
    Game1000/thousandgamequeryhandler.cpp \
    HTTPServer/httpserver.cpp \
    HTTPServer/httprequest.cpp \
    HTTPServer/httpresponse.cpp \
    HTTPServer/httpconnection.cpp

HEADERS  += \
    mainserver.h \
    abstractgameserver.h \
    config.h \
    description.h \
    gameserverfactory.h \
    thousandgameserverfactory.h \
    connectionmanager.h \
    thousandgameserver.h \
    protocol.h \
    abstractqueryhandler.h \
    abstractdataparser.h \
    card.h \
    tablemodel.h \
    Game1000/thousandgamedataparser.h \
    Game1000/gamethousand.h \
    Game1000/thousandgamequeryhandler.h \
    HTTPServer/httpserver.h \
    HTTPServer/httprequest.h \
    HTTPServer/httpresponse.h \
    HTTPServer/httpconnection.h \
    HTTPServer/httpdefs.h

OTHER_FILES += \
    ProtocolDescription.txt
