#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T10:46:11
#
#-------------------------------------------------

QT       += core gui serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cstagecontroller.cpp \
    hardwareserialui.cpp

HEADERS  += mainwindow.h \
    icontrolinterface.h \
    cstagecontroller.h \
    iuieventhandler.h \
    hardwareserialui.h

FORMS    += mainwindow.ui

CONFIG += c++11

