#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T14:07:11
#
#-------------------------------------------------

QT       += widgets

TARGET = sepiaFilter
TEMPLATE = lib

DEFINES += SEPIAFILTER_LIBRARY

SOURCES += sepiafilter.cpp \
    dialog.cpp

HEADERS += sepiafilter.h\
        sepiafilter_global.h \
    ../../../include/plugininterface.h \
    dialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    dialog.ui


CONFIG  += plugin
