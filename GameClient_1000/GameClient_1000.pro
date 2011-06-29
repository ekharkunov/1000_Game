#-------------------------------------------------
#
# Project created by QtCreator 2011-05-30T22:44:33
#
#-------------------------------------------------

QT       += core gui\
             network

TARGET = GameClient_1000
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractclient.cpp \
    abstractdataparser.cpp \
    thousandclient.cpp \
    thousandclientdataparser.cpp \
    gamethousand.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    abstractclient.h \
    protocol.h \
    abstractdataparser.h \
    thousandclient.h \
    thousandclientdataparser.h \
    card.h \
    gamethousand.h \
    player.h

OTHER_FILES += \
    ProtocolDescription.txt


FORMS += \
    mainwindow.ui

RESOURCES += \
    media.qrc
