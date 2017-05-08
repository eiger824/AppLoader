#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T12:21:32
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = apploader
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/mainwindow.cpp \
    src/apploader.cpp \
    src/main.cpp \
    src/dbusdaemon.cpp

HEADERS  += include/mainwindow.h \
    include/apploader.h \
    include/dbusdaemon.h

FORMS    += \
    forms/mainwindow.ui

RESOURCES += \
    res/resources.qrc

DBUS_ADAPTORS += \
    interface/se.mydns.mysland.DBusDaemon.xml

DBUS_INTERFACES += \
    interface/se.mydns.mysland.DBusDaemon.xml

DISTFILES += \
    interface/se.mydns.mysland.DBusDaemon.xml

LIBS += -lglog
