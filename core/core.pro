#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T16:38:25
#
#-------------------------------------------------

QT       -= gui

TARGET = core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

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
        core.cpp \
    block/transaction/registertransaction.cpp \
    block/transaction/transferencetransaction.cpp \
    block/block.cpp \
    block/blockchain.cpp \
    block/genesis.cpp \
    block/header.cpp

HEADERS += \
        core.h \
        core_global.h \ 
    block/transaction/atransaction.h \
    block/transaction/registertransaction.h \
    block/transaction/transferencetransaction.h \
    block/block.h \
    block/blockchain.h \
    block/genesis.h \
    block/header.h \
    asignable.h \
    iverifiable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


