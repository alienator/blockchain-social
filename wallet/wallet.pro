#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T10:28:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wallet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tx.cpp

HEADERS += \
        mainwindow.h \
    tx.h

FORMS += \
        mainwindow.ui

unix:!macx: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

unix:!macx: LIBS += -L$$OUT_PWD/../dbaccess/ -ldbaccess

INCLUDEPATH += $$PWD/../dbaccess
DEPENDPATH += $$PWD/../dbaccess

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lmongoc-1.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/include/libmongoc-1.0
DEPENDPATH += $$PWD/../../../../../../usr/local/include/libmongoc-1.0

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lbson-1.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/include/libbson-1.0
DEPENDPATH += $$PWD/../../../../../../usr/local/include/libbson-1.0
