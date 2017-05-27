#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T19:08:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FEAapp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    celement.cpp \
    cinstance.cpp \
    cload.cpp \
    cconstraint.cpp \
    cinput.cpp

HEADERS  += mainwindow.h \
    cnode.h \
    cmaterial.h \
    celement.h \
    cinstance.h \
    cload.h \
    cconstraint.h \
    cinput.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\Software\Qt\Eigen
