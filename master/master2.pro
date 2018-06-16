#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T04:22:52
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = master2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    qss_res.cpp \
    report.cpp \
    master_controller.cpp \
    user_controller.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    login.h \
    qss_res.h \
    title_bar.h \
    datastruct.h

FORMS    += mainwindow.ui \
    login.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    login_res.qrc
