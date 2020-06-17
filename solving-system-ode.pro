#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T17:57:01
#
#-------------------------------------------------
unix: QWT_ROOT = /usr/local/qwt-6.1.0
win32: QWT_ROOT = C:/Qt/Qwt-6.1.0
osx: QWT_ROOT=/usr/local/qwt-6.1.5
include ( $${QWT_ROOT}/features/qwt.prf )

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = solving-system-ode
TEMPLATE = app


SOURCES += main.cpp\
        curves.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    curves.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
