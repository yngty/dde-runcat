#-------------------------------------------------
#
# Project created by QtCreator 2022-01-04T19:19:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = $$qtLibraryTarget(dde-runcat)

TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 plugin

DISTFILES       += runcat.json

SOURCES += \
    runcatplugin.cpp \
    runcatwidget.cpp \
    systemmanager.cpp

HEADERS += \
    runcatplugin.h \
    runcatwidget.h \
    systemmanager.h

unix {
    target.path = /usr/lib/dde-dock/plugins/
    INSTALLS += target
}

RESOURCES += \
    cat.qrc
