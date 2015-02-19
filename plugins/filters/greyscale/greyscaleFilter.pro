#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T15:20:47
#
#-------------------------------------------------

QT       += widgets

TARGET = greyscaleFilter
TEMPLATE = lib

DEFINES += GRAYSCALEEFFECT_LIBRARY

SOURCES += \
    greyscalefilter.cpp

HEADERS +=\
        ../../filterplugininterface.h \
    greyscalefilter.h \
    greyscalefilter_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += plugin
