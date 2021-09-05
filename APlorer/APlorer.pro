QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SearchWindow.cpp \
    aplmainwindow.cpp \
    aplsingleapplication.cpp \
    customstyle.cpp \
    driverwidget.cpp \
    everythingutil.cpp \
    main.cpp \
    mytabwidget.cpp \
    tabbar.cpp

HEADERS += \
    SearchWindow.h \
    aplmainwindow.h \
    aplsingleapplication.h \
    customstyle.h \
    driverwidget.h \
    everythingutil.h \
    mytabwidget.h \
    tabbar.h

FORMS += \
    SearchWindow.ui \
    aplmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 临时文件存放位置
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj

# 通用模块引入
include(.\sys\qtsingleapplication\qtsingleapplication.pri)  # 应用单实例

RESOURCES += \
    icon.qrc


INCLUDEPATH += $$PWD/include

LIBS += -L$$PWD/lib -lEverything64

DISTFILES +=
