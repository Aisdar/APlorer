/********************************************************************************
** Form generated from reading UI file 'aplmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLMAINWINDOW_H
#define UI_APLMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "mytabwidget.h"

QT_BEGIN_NAMESPACE

class Ui_aplMainWindow
{
public:
    QAction *actionnewFile;
    QAction *actionforward;
    QAction *actionbackward;
    QAction *actionhome;
    QAction *actioncopy;
    QAction *actionpaste;
    QAction *actioncut;
    QAction *actionshare;
    QAction *actiondelete;
    QAction *actionempty;
    QAction *actionrefresh;
    QAction *actionlayout;
    QAction *actionsetting;
    QAction *actionbigIcon;
    QAction *actionsmallIcon;
    QAction *actiondetails;
    QAction *actionSearch;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QComboBox *pathBox;
    QLineEdit *searchBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_backward;
    QToolButton *btn_forward;
    QToolButton *btn_backspace;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QTreeView *directoryTree;
    MyTabWidget *brower;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *aplMainWindow)
    {
        if (aplMainWindow->objectName().isEmpty())
            aplMainWindow->setObjectName(QString::fromUtf8("aplMainWindow"));
        aplMainWindow->resize(1250, 740);
        actionnewFile = new QAction(aplMainWindow);
        actionnewFile->setObjectName(QString::fromUtf8("actionnewFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/default theme/file-add-line.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionnewFile->setIcon(icon);
        actionforward = new QAction(aplMainWindow);
        actionforward->setObjectName(QString::fromUtf8("actionforward"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/default theme/forward-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionforward->setIcon(icon1);
        actionbackward = new QAction(aplMainWindow);
        actionbackward->setObjectName(QString::fromUtf8("actionbackward"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/default theme/back-arrow-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbackward->setIcon(icon2);
        actionhome = new QAction(aplMainWindow);
        actionhome->setObjectName(QString::fromUtf8("actionhome"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/default theme/home-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionhome->setIcon(icon3);
        actioncopy = new QAction(aplMainWindow);
        actioncopy->setObjectName(QString::fromUtf8("actioncopy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/default theme/file-copy-2-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncopy->setIcon(icon4);
        actionpaste = new QAction(aplMainWindow);
        actionpaste->setObjectName(QString::fromUtf8("actionpaste"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/default theme/sticker-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpaste->setIcon(icon5);
        actioncut = new QAction(aplMainWindow);
        actioncut->setObjectName(QString::fromUtf8("actioncut"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/default theme/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncut->setIcon(icon6);
        actionshare = new QAction(aplMainWindow);
        actionshare->setObjectName(QString::fromUtf8("actionshare"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/default theme/share-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionshare->setIcon(icon7);
        actiondelete = new QAction(aplMainWindow);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/default theme/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiondelete->setIcon(icon8);
        actionempty = new QAction(aplMainWindow);
        actionempty->setObjectName(QString::fromUtf8("actionempty"));
        actionrefresh = new QAction(aplMainWindow);
        actionrefresh->setObjectName(QString::fromUtf8("actionrefresh"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/default theme/rotate-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrefresh->setIcon(icon9);
        actionlayout = new QAction(aplMainWindow);
        actionlayout->setObjectName(QString::fromUtf8("actionlayout"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/default theme/grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionlayout->setIcon(icon10);
        actionsetting = new QAction(aplMainWindow);
        actionsetting->setObjectName(QString::fromUtf8("actionsetting"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/default theme/settings-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsetting->setIcon(icon11);
        actionbigIcon = new QAction(aplMainWindow);
        actionbigIcon->setObjectName(QString::fromUtf8("actionbigIcon"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icon/default theme/grid-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbigIcon->setIcon(icon12);
        actionsmallIcon = new QAction(aplMainWindow);
        actionsmallIcon->setObjectName(QString::fromUtf8("actionsmallIcon"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icon/default theme/grid-_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsmallIcon->setIcon(icon13);
        actiondetails = new QAction(aplMainWindow);
        actiondetails->setObjectName(QString::fromUtf8("actiondetails"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icon/default theme/layout-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiondetails->setIcon(icon14);
        actionSearch = new QAction(aplMainWindow);
        actionSearch->setObjectName(QString::fromUtf8("actionSearch"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Search.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearch->setIcon(icon15);
        centralwidget = new QWidget(aplMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pathBox = new QComboBox(centralwidget);
        pathBox->setObjectName(QString::fromUtf8("pathBox"));
        pathBox->setMinimumSize(QSize(0, 32));

        gridLayout->addWidget(pathBox, 0, 1, 1, 1);

        searchBox = new QLineEdit(centralwidget);
        searchBox->setObjectName(QString::fromUtf8("searchBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchBox->sizePolicy().hasHeightForWidth());
        searchBox->setSizePolicy(sizePolicy);
        searchBox->setMinimumSize(QSize(250, 34));

        gridLayout->addWidget(searchBox, 0, 2, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(290, 50));
        widget->setMaximumSize(QSize(290, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_backward = new QToolButton(widget);
        btn_backward->setObjectName(QString::fromUtf8("btn_backward"));
        sizePolicy.setHeightForWidth(btn_backward->sizePolicy().hasHeightForWidth());
        btn_backward->setSizePolicy(sizePolicy);
        btn_backward->setMinimumSize(QSize(65, 35));

        horizontalLayout->addWidget(btn_backward);

        btn_forward = new QToolButton(widget);
        btn_forward->setObjectName(QString::fromUtf8("btn_forward"));
        btn_forward->setMinimumSize(QSize(65, 35));

        horizontalLayout->addWidget(btn_forward);

        btn_backspace = new QToolButton(widget);
        btn_backspace->setObjectName(QString::fromUtf8("btn_backspace"));
        btn_backspace->setMinimumSize(QSize(40, 35));

        horizontalLayout->addWidget(btn_backspace);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter = new QSplitter(frame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        directoryTree = new QTreeView(splitter);
        directoryTree->setObjectName(QString::fromUtf8("directoryTree"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(directoryTree->sizePolicy().hasHeightForWidth());
        directoryTree->setSizePolicy(sizePolicy2);
        directoryTree->setMinimumSize(QSize(0, 0));
        directoryTree->setMaximumSize(QSize(300, 800));
        directoryTree->setAcceptDrops(false);
        splitter->addWidget(directoryTree);

        horizontalLayout_2->addWidget(splitter);

        brower = new MyTabWidget(frame);
        brower->setObjectName(QString::fromUtf8("brower"));
        sizePolicy1.setHeightForWidth(brower->sizePolicy().hasHeightForWidth());
        brower->setSizePolicy(sizePolicy1);
        brower->setMinimumSize(QSize(915, 570));

        horizontalLayout_2->addWidget(brower);


        gridLayout->addWidget(frame, 1, 0, 2, 3);

        aplMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(aplMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        aplMainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(aplMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy3);
        toolBar->setMinimumSize(QSize(0, 0));
        toolBar->setIconSize(QSize(45, 35));
        aplMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionnewFile);
        toolBar->addAction(actionhome);
        toolBar->addSeparator();
        toolBar->addAction(actioncut);
        toolBar->addAction(actioncopy);
        toolBar->addAction(actionpaste);
        toolBar->addAction(actionshare);
        toolBar->addAction(actiondelete);
        toolBar->addSeparator();
        toolBar->addAction(actionsetting);
        toolBar->addAction(actionSearch);

        retranslateUi(aplMainWindow);

        QMetaObject::connectSlotsByName(aplMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *aplMainWindow)
    {
        aplMainWindow->setWindowTitle(QApplication::translate("aplMainWindow", "MainWindow", nullptr));
        actionnewFile->setText(QApplication::translate("aplMainWindow", "newFile", nullptr));
#ifndef QT_NO_TOOLTIP
        actionnewFile->setToolTip(QApplication::translate("aplMainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_NO_TOOLTIP
        actionforward->setText(QApplication::translate("aplMainWindow", "forward", nullptr));
#ifndef QT_NO_TOOLTIP
        actionforward->setToolTip(QApplication::translate("aplMainWindow", "\345\211\215\350\277\233", nullptr));
#endif // QT_NO_TOOLTIP
        actionbackward->setText(QApplication::translate("aplMainWindow", "backward", nullptr));
#ifndef QT_NO_TOOLTIP
        actionbackward->setToolTip(QApplication::translate("aplMainWindow", "\345\220\216\351\200\200", nullptr));
#endif // QT_NO_TOOLTIP
        actionhome->setText(QApplication::translate("aplMainWindow", "home", nullptr));
#ifndef QT_NO_TOOLTIP
        actionhome->setToolTip(QApplication::translate("aplMainWindow", "\345\233\236\345\210\260\344\270\273\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
        actioncopy->setText(QApplication::translate("aplMainWindow", "copy", nullptr));
#ifndef QT_NO_TOOLTIP
        actioncopy->setToolTip(QApplication::translate("aplMainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_NO_TOOLTIP
        actionpaste->setText(QApplication::translate("aplMainWindow", "paste", nullptr));
#ifndef QT_NO_TOOLTIP
        actionpaste->setToolTip(QApplication::translate("aplMainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_NO_TOOLTIP
        actioncut->setText(QApplication::translate("aplMainWindow", "cut", nullptr));
#ifndef QT_NO_TOOLTIP
        actioncut->setToolTip(QApplication::translate("aplMainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_NO_TOOLTIP
        actionshare->setText(QApplication::translate("aplMainWindow", "share", nullptr));
#ifndef QT_NO_TOOLTIP
        actionshare->setToolTip(QApplication::translate("aplMainWindow", "\345\210\206\344\272\253", nullptr));
#endif // QT_NO_TOOLTIP
        actiondelete->setText(QApplication::translate("aplMainWindow", "delete", nullptr));
#ifndef QT_NO_TOOLTIP
        actiondelete->setToolTip(QApplication::translate("aplMainWindow", "\345\210\240\351\231\244", nullptr));
#endif // QT_NO_TOOLTIP
        actionempty->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionempty->setToolTip(QApplication::translate("aplMainWindow", "\347\251\272\347\232\204\345\215\240\344\275\215\347\275\256", nullptr));
#endif // QT_NO_TOOLTIP
        actionrefresh->setText(QApplication::translate("aplMainWindow", "refresh", nullptr));
#ifndef QT_NO_TOOLTIP
        actionrefresh->setToolTip(QApplication::translate("aplMainWindow", "\345\210\267\346\226\260", nullptr));
#endif // QT_NO_TOOLTIP
        actionlayout->setText(QApplication::translate("aplMainWindow", "layout", nullptr));
#ifndef QT_NO_TOOLTIP
        actionlayout->setToolTip(QApplication::translate("aplMainWindow", "\345\270\203\345\261\200", nullptr));
#endif // QT_NO_TOOLTIP
        actionsetting->setText(QApplication::translate("aplMainWindow", "setting", nullptr));
#ifndef QT_NO_TOOLTIP
        actionsetting->setToolTip(QApplication::translate("aplMainWindow", "\350\256\276\347\275\256", nullptr));
#endif // QT_NO_TOOLTIP
        actionbigIcon->setText(QApplication::translate("aplMainWindow", "\345\244\247\345\233\276\346\240\207", nullptr));
#ifndef QT_NO_TOOLTIP
        actionbigIcon->setToolTip(QApplication::translate("aplMainWindow", "\345\244\247\345\233\276\346\240\207", nullptr));
#endif // QT_NO_TOOLTIP
        actionsmallIcon->setText(QApplication::translate("aplMainWindow", "\345\260\217\345\233\276\346\240\207", nullptr));
#ifndef QT_NO_TOOLTIP
        actionsmallIcon->setToolTip(QApplication::translate("aplMainWindow", "\345\260\217\345\233\276\346\240\207", nullptr));
#endif // QT_NO_TOOLTIP
        actiondetails->setText(QApplication::translate("aplMainWindow", "\350\257\246\347\273\206\345\206\205\345\256\271", nullptr));
#ifndef QT_NO_TOOLTIP
        actiondetails->setToolTip(QApplication::translate("aplMainWindow", "\350\257\246\347\273\206\345\206\205\345\256\271", nullptr));
#endif // QT_NO_TOOLTIP
        actionSearch->setText(QApplication::translate("aplMainWindow", "Search", nullptr));
        btn_backward->setText(QString());
        btn_forward->setText(QString());
        btn_backspace->setText(QString());
        toolBar->setWindowTitle(QApplication::translate("aplMainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aplMainWindow: public Ui_aplMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLMAINWINDOW_H
