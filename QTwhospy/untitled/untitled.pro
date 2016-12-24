#-------------------------------------------------
#
# Project created by QtCreator 2016-12-09T13:30:50
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joinodbc.cpp \
    gamemain.cpp \
    qt5serialport/datadeal.cpp \
    qt5serialport/serial.cpp \
    text.cpp

HEADERS  += mainwindow.h \
    joinodbc.h \
    gamemain.h \
    qt5serialport/datadeal.h \
    qt5serialport/serial.h \
    text.h

FORMS    += mainwindow.ui \
    qt5serialport/serial.ui \
    text.ui

RESOURCES += \
    resource.qrc
