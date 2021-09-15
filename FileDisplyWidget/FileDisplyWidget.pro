QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bigicondelegate.cpp \
    contentdelegate.cpp \
    detaildelegate.cpp \
    dtaildelegate2.cpp \
    filedisplaywidget.cpp \
    listdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    mytableview.cpp

HEADERS += \
    bigicondelegate.h \
    contentdelegate.h \
    data.h \
    detaildelegate.h \
    dtaildelegate2.h \
    filedisplaywidget.h \
    listdelegate.h \
    mainwindow.h \
    mytableview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
