INCLUDEPATH	+= $$PWD
DEPENDPATH      += $$PWD
HEADERS		+= $$PWD/qtsinglecoreapplication.h $$PWD/qtlocalpeer.h
SOURCES		+= $$PWD/qtsinglecoreapplication.cpp $$PWD/qtlocalpeer.cpp

QT *= network
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:contains(TEMPLATE, lib):contains(CONFIG, shared) {
    DEFINES += QT_QTSINGLECOREAPPLICATION_EXPORT=__declspec(dllexport)
}
