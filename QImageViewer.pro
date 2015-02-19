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
        mainwindow.cpp \
    effectplugininterface.cpp

HEADERS  += mainwindow.h \
    effectplugininterface.h

FORMS    += mainwindow.ui

CONFIG   += c++11
