QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SearchWindow.cpp \
    aplmainwindow.cpp \
    bigicondelegate.cpp \
    contentdelegate.cpp \
    countthefilesizeofeachcategory.cpp \
    cshell.cpp \
    customstyle.cpp \
    detaildelegate.cpp \
    detaildelegate2.cpp \
    driverwidget.cpp \
    everythingutil.cpp \
    listdelegate.cpp \
    main.cpp \
    mytableview.cpp \
    mytabwidget.cpp \
    mytreeview.cpp \
    tabbar.cpp \

HEADERS += \
    CShell.h \
    SearchWindow.h \
    aplmainwindow.h \
    bigicondelegate.h \
    contentdelegate.h \
    countthefilesizeofeachcategory.h \
    customstyle.h \
    detaildelegate.h \
    detaildelegate2.h \
    driverwidget.h \
    everythingutil.h \
    listdelegate.h \
    mytableview.h \
    mytabwidget.h \
    mytreeview.h \
    tabbar.h \

FORMS += \
    SearchWindow.ui \
    aplmainwindow.ui \

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

DISTFILES += \
    assert/assert.pri

win32: LIBS += -lOle32


include (assert/assert.pri)
