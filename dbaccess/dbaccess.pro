#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T16:21:23
#
#-------------------------------------------------

QT       -= gui

TARGET = dbaccess
TEMPLATE = lib

DEFINES += DBACCESS_LIBRARY

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
        dbaccess.cpp \
    mongodb/headermongodb.cpp \
    mongodb/mongodb.cpp \
    mongodb/registertransactionmongodb.cpp \
    mongodb/transferecetransactionmongodb.cpp

HEADERS += \
        dbaccess.h \
        dbaccess_global.h \ 
    iadapter.h \
    mongodb/headermongodb.h \
    mongodb/mongodb.h \
    mongodb/registertransactionmongodb.h \
    mongodb/transferecetransactionmongodb.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lmongoc-1.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/include/libmongoc-1.0
DEPENDPATH += $$PWD/../../../../../../usr/local/include/libmongoc-1.0

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lbson-1.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/include/libbson-1.0
DEPENDPATH += $$PWD/../../../../../../usr/local/include/libbson-1.0
