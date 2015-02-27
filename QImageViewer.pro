#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T22:48:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QImageViewer
TEMPLATE = app


SOURCES += main.cpp\
        src/mainwindow.cpp \
    src/imagemanager.cpp \
    src/plugininterface.cpp \
    src/pluginmanager.cpp \
    src/manageplugins.cpp

HEADERS  += include/mainwindow.h \
    include/imagemanager.h \
    include/plugininterface.h \
    include/pluginmanager.h \
    include/manageplugins.h

FORMS    += mainwindow.ui \
    manageplugins.ui

CONFIG   += c++11
