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
    greyscalefilter.cpp \
    dialog.cpp

HEADERS +=\
        ../../../plugininterface.h \
    greyscalefilter.h \
    greyscalefilter_global.h \
    dialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += plugin

FORMS += \
    dialog.ui
