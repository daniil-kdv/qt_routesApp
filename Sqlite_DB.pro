#-------------------------------------------------
#
# Project created by QtCreator 2021-01-03T20:23:27
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sqlite_DB
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    employeeinfo.cpp \
    userwindow.cpp \
    print.cpp

HEADERS  += login.h \
    employeeinfo.h \
    userwindow.h \
    print.h

FORMS    += login.ui \
    employeeinfo.ui \
    userwindow.ui \
    print.ui
