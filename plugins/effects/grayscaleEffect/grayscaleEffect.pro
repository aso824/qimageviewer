#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T15:20:47
#
#-------------------------------------------------

QT       += widgets

TARGET = grayscaleEffect
TEMPLATE = lib

DEFINES += GRAYSCALEEFFECT_LIBRARY

SOURCES += grayscaleeffect.cpp

HEADERS += grayscaleeffect.h\
        grayscaleeffect_global.h\
        ../../effectplugininterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += plugin
