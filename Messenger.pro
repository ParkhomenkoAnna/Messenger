#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T21:51:41
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    adduser.cpp \
    udpserver.cpp \
    login_manager.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    adduser.h \
    udpserver.h \
    login_manager.h

FORMS    += mainwindow.ui \
    dialog.ui \
    adduser.ui \
    login_manager.ui
