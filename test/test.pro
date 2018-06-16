#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T17:29:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    netcontroller.cpp

HEADERS  += mainwindow.h \
    netcontroller.h \
    constant.h

FORMS    += mainwindow.ui
