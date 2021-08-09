/********************************************************************************
** Form generated from reading UI file 'aplmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLMAINWINDOW_H
#define UI_APLMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

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
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QComboBox *pathBox;
    QTreeView *directoryTree;
    QLineEdit *searchBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_backward;
    QToolButton *btn_forward;
    QToolButton *btn_backspace;
    QTabWidget *browser;
    QWidget *home;
    QWidget *scaned;
    QGridLayout *gridLayout_2;
    QPushButton *btn_doc;
    QPushButton *btn_collect;
    QPushButton *btn_video;
    QPushButton *btn_picture;
    QPushButton *btn_zip;
    QPushButton *btn_music;
    QWidget *tab_2;
    QWidget *tab;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *aplMainWindow)
    {
        if (aplMainWindow->objectName().isEmpty())
            aplMainWindow->setObjectName(QStringLiteral("aplMainWindow"));
        aplMainWindow->resize(1244, 713);
        actionnewFile = new QAction(aplMainWindow);
        actionnewFile->setObjectName(QStringLiteral("actionnewFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/default theme/file-add-line.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionnewFile->setIcon(icon);
        actionforward = new QAction(aplMainWindow);
        actionforward->setObjectName(QStringLiteral("actionforward"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/default theme/forward-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionforward->setIcon(icon1);
        actionbackward = new QAction(aplMainWindow);
        actionbackward->setObjectName(QStringLiteral("actionbackward"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/default theme/back-arrow-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbackward->setIcon(icon2);
        actionhome = new QAction(aplMainWindow);
        actionhome->setObjectName(QStringLiteral("actionhome"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/default theme/home-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionhome->setIcon(icon3);
        actioncopy = new QAction(aplMainWindow);
        actioncopy->setObjectName(QStringLiteral("actioncopy"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/default theme/file-copy-2-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncopy->setIcon(icon4);
        actionpaste = new QAction(aplMainWindow);
        actionpaste->setObjectName(QStringLiteral("actionpaste"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/default theme/sticker-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpaste->setIcon(icon5);
        actioncut = new QAction(aplMainWindow);
        actioncut->setObjectName(QStringLiteral("actioncut"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/default theme/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncut->setIcon(icon6);
        actionshare = new QAction(aplMainWindow);
        actionshare->setObjectName(QStringLiteral("actionshare"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/default theme/share-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionshare->setIcon(icon7);
        actiondelete = new QAction(aplMainWindow);
        actiondelete->setObjectName(QStringLiteral("actiondelete"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/default theme/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiondelete->setIcon(icon8);
        actionempty = new QAction(aplMainWindow);
        actionempty->setObjectName(QStringLiteral("actionempty"));
        actionrefresh = new QAction(aplMainWindow);
        actionrefresh->setObjectName(QStringLiteral("actionrefresh"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/default theme/rotate-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrefresh->setIcon(icon9);
        actionlayout = new QAction(aplMainWindow);
        actionlayout->setObjectName(QStringLiteral("actionlayout"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/default theme/grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionlayout->setIcon(icon10);
        actionsetting = new QAction(aplMainWindow);
        actionsetting->setObjectName(QStringLiteral("actionsetting"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/default theme/settings-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsetting->setIcon(icon11);
        actionbigIcon = new QAction(aplMainWindow);
        actionbigIcon->setObjectName(QStringLiteral("actionbigIcon"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icon/default theme/grid-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbigIcon->setIcon(icon12);
        actionsmallIcon = new QAction(aplMainWindow);
        actionsmallIcon->setObjectName(QStringLiteral("actionsmallIcon"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icon/default theme/grid-_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsmallIcon->setIcon(icon13);
        actiondetails = new QAction(aplMainWindow);
        actiondetails->setObjectName(QStringLiteral("actiondetails"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icon/default theme/layout-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiondetails->setIcon(icon14);
        centralwidget = new QWidget(aplMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pathBox = new QComboBox(centralwidget);
        pathBox->setObjectName(QStringLiteral("pathBox"));
        pathBox->setMinimumSize(QSize(0, 32));

        gridLayout->addWidget(pathBox, 0, 1, 1, 1);

        directoryTree = new QTreeView(centralwidget);
        directoryTree->setObjectName(QStringLiteral("directoryTree"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(directoryTree->sizePolicy().hasHeightForWidth());
        directoryTree->setSizePolicy(sizePolicy);
        directoryTree->setMinimumSize(QSize(292, 555));
        directoryTree->setAcceptDrops(false);

        gridLayout->addWidget(directoryTree, 1, 0, 2, 1);

        searchBox = new QLineEdit(centralwidget);
        searchBox->setObjectName(QStringLiteral("searchBox"));
        sizePolicy.setHeightForWidth(searchBox->sizePolicy().hasHeightForWidth());
        searchBox->setSizePolicy(sizePolicy);
        searchBox->setMinimumSize(QSize(250, 34));

        gridLayout->addWidget(searchBox, 0, 2, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btn_backward = new QToolButton(widget);
        btn_backward->setObjectName(QStringLiteral("btn_backward"));
        sizePolicy.setHeightForWidth(btn_backward->sizePolicy().hasHeightForWidth());
        btn_backward->setSizePolicy(sizePolicy);
        btn_backward->setMinimumSize(QSize(65, 35));

        horizontalLayout->addWidget(btn_backward);

        btn_forward = new QToolButton(widget);
        btn_forward->setObjectName(QStringLiteral("btn_forward"));
        btn_forward->setMinimumSize(QSize(65, 35));

        horizontalLayout->addWidget(btn_forward);

        btn_backspace = new QToolButton(widget);
        btn_backspace->setObjectName(QStringLiteral("btn_backspace"));
        btn_backspace->setMinimumSize(QSize(40, 35));

        horizontalLayout->addWidget(btn_backspace);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        browser = new QTabWidget(centralwidget);
        browser->setObjectName(QStringLiteral("browser"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(browser->sizePolicy().hasHeightForWidth());
        browser->setSizePolicy(sizePolicy1);
        browser->setIconSize(QSize(20, 30));
        browser->setElideMode(Qt::ElideNone);
        browser->setTabsClosable(true);
        browser->setMovable(true);
        browser->setTabBarAutoHide(false);
        home = new QWidget();
        home->setObjectName(QStringLiteral("home"));
        scaned = new QWidget(home);
        scaned->setObjectName(QStringLiteral("scaned"));
        scaned->setGeometry(QRect(130, 290, 600, 234));
        sizePolicy.setHeightForWidth(scaned->sizePolicy().hasHeightForWidth());
        scaned->setSizePolicy(sizePolicy);
        scaned->setMinimumSize(QSize(600, 234));
        scaned->setFocusPolicy(Qt::StrongFocus);
        gridLayout_2 = new QGridLayout(scaned);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btn_doc = new QPushButton(scaned);
        btn_doc->setObjectName(QStringLiteral("btn_doc"));
        sizePolicy.setHeightForWidth(btn_doc->sizePolicy().hasHeightForWidth());
        btn_doc->setSizePolicy(sizePolicy);
        btn_doc->setMinimumSize(QSize(100, 50));
        btn_doc->setFocusPolicy(Qt::StrongFocus);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icon/default theme/file-pdf-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_doc->setIcon(icon15);
        btn_doc->setAutoDefault(false);

        gridLayout_2->addWidget(btn_doc, 1, 0, 1, 1);

        btn_collect = new QPushButton(scaned);
        btn_collect->setObjectName(QStringLiteral("btn_collect"));
        sizePolicy.setHeightForWidth(btn_collect->sizePolicy().hasHeightForWidth());
        btn_collect->setSizePolicy(sizePolicy);
        btn_collect->setMinimumSize(QSize(100, 50));
        btn_collect->setFocusPolicy(Qt::StrongFocus);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icon/default theme/folder-info-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_collect->setIcon(icon16);
        btn_collect->setAutoDefault(false);

        gridLayout_2->addWidget(btn_collect, 1, 2, 1, 1);

        btn_video = new QPushButton(scaned);
        btn_video->setObjectName(QStringLiteral("btn_video"));
        sizePolicy.setHeightForWidth(btn_video->sizePolicy().hasHeightForWidth());
        btn_video->setSizePolicy(sizePolicy);
        btn_video->setMinimumSize(QSize(100, 50));
        btn_video->setFocusPolicy(Qt::StrongFocus);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icon/default theme/video-gallery.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_video->setIcon(icon17);
        btn_video->setAutoDefault(false);

        gridLayout_2->addWidget(btn_video, 0, 1, 1, 1);

        btn_picture = new QPushButton(scaned);
        btn_picture->setObjectName(QStringLiteral("btn_picture"));
        sizePolicy.setHeightForWidth(btn_picture->sizePolicy().hasHeightForWidth());
        btn_picture->setSizePolicy(sizePolicy);
        btn_picture->setMinimumSize(QSize(100, 50));
        btn_picture->setFocusPolicy(Qt::StrongFocus);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icon/default theme/photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_picture->setIcon(icon18);
        btn_picture->setAutoDefault(false);

        gridLayout_2->addWidget(btn_picture, 0, 2, 1, 1);

        btn_zip = new QPushButton(scaned);
        btn_zip->setObjectName(QStringLiteral("btn_zip"));
        sizePolicy.setHeightForWidth(btn_zip->sizePolicy().hasHeightForWidth());
        btn_zip->setSizePolicy(sizePolicy);
        btn_zip->setMinimumSize(QSize(100, 50));
        btn_zip->setFocusPolicy(Qt::StrongFocus);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icon/default theme/folder-zip-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_zip->setIcon(icon19);
        btn_zip->setAutoDefault(false);

        gridLayout_2->addWidget(btn_zip, 1, 1, 1, 1);

        btn_music = new QPushButton(scaned);
        btn_music->setObjectName(QStringLiteral("btn_music"));
        sizePolicy.setHeightForWidth(btn_music->sizePolicy().hasHeightForWidth());
        btn_music->setSizePolicy(sizePolicy);
        btn_music->setMinimumSize(QSize(100, 50));
        btn_music->setFocusPolicy(Qt::StrongFocus);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icon/default theme/folder-music-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_music->setIcon(icon20);
        btn_music->setAutoDefault(false);

        gridLayout_2->addWidget(btn_music, 0, 0, 1, 1);

        browser->addTab(home, icon3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        browser->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icon/default theme/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        browser->addTab(tab, icon21, QString());

        gridLayout->addWidget(browser, 1, 1, 2, 2);

        aplMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(aplMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        aplMainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(aplMainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy2);
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

        retranslateUi(aplMainWindow);

        browser->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(aplMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *aplMainWindow)
    {
        aplMainWindow->setWindowTitle(QApplication::translate("aplMainWindow", "MainWindow", Q_NULLPTR));
        actionnewFile->setText(QApplication::translate("aplMainWindow", "newFile", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionnewFile->setToolTip(QApplication::translate("aplMainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionforward->setText(QApplication::translate("aplMainWindow", "forward", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionforward->setToolTip(QApplication::translate("aplMainWindow", "\345\211\215\350\277\233", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionbackward->setText(QApplication::translate("aplMainWindow", "backward", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbackward->setToolTip(QApplication::translate("aplMainWindow", "\345\220\216\351\200\200", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionhome->setText(QApplication::translate("aplMainWindow", "home", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionhome->setToolTip(QApplication::translate("aplMainWindow", "\345\233\236\345\210\260\344\270\273\351\241\265", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actioncopy->setText(QApplication::translate("aplMainWindow", "copy", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actioncopy->setToolTip(QApplication::translate("aplMainWindow", "\345\244\215\345\210\266", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionpaste->setText(QApplication::translate("aplMainWindow", "paste", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionpaste->setToolTip(QApplication::translate("aplMainWindow", "\347\262\230\350\264\264", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actioncut->setText(QApplication::translate("aplMainWindow", "cut", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actioncut->setToolTip(QApplication::translate("aplMainWindow", "\345\211\252\345\210\207", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionshare->setText(QApplication::translate("aplMainWindow", "share", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionshare->setToolTip(QApplication::translate("aplMainWindow", "\345\210\206\344\272\253", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actiondelete->setText(QApplication::translate("aplMainWindow", "delete", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actiondelete->setToolTip(QApplication::translate("aplMainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionempty->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionempty->setToolTip(QApplication::translate("aplMainWindow", "\347\251\272\347\232\204\345\215\240\344\275\215\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionrefresh->setText(QApplication::translate("aplMainWindow", "refresh", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionrefresh->setToolTip(QApplication::translate("aplMainWindow", "\345\210\267\346\226\260", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionlayout->setText(QApplication::translate("aplMainWindow", "layout", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionlayout->setToolTip(QApplication::translate("aplMainWindow", "\345\270\203\345\261\200", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionsetting->setText(QApplication::translate("aplMainWindow", "setting", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionsetting->setToolTip(QApplication::translate("aplMainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionbigIcon->setText(QApplication::translate("aplMainWindow", "\345\244\247\345\233\276\346\240\207", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbigIcon->setToolTip(QApplication::translate("aplMainWindow", "\345\244\247\345\233\276\346\240\207", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionsmallIcon->setText(QApplication::translate("aplMainWindow", "\345\260\217\345\233\276\346\240\207", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionsmallIcon->setToolTip(QApplication::translate("aplMainWindow", "\345\260\217\345\233\276\346\240\207", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actiondetails->setText(QApplication::translate("aplMainWindow", "\350\257\246\347\273\206\345\206\205\345\256\271", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actiondetails->setToolTip(QApplication::translate("aplMainWindow", "\350\257\246\347\273\206\345\206\205\345\256\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_backward->setText(QString());
        btn_forward->setText(QString());
        btn_backspace->setText(QString());
        btn_doc->setText(QApplication::translate("aplMainWindow", "   \346\226\207\346\241\243", Q_NULLPTR));
        btn_collect->setText(QApplication::translate("aplMainWindow", "   \346\224\266\350\227\217", Q_NULLPTR));
        btn_video->setText(QApplication::translate("aplMainWindow", " \350\247\206\351\242\221", Q_NULLPTR));
        btn_picture->setText(QApplication::translate("aplMainWindow", "\345\233\276\347\211\207", Q_NULLPTR));
        btn_zip->setText(QApplication::translate("aplMainWindow", " \345\216\213\347\274\251\346\226\207\344\273\266", Q_NULLPTR));
        btn_music->setText(QApplication::translate("aplMainWindow", " \351\237\263\344\271\220", Q_NULLPTR));
        browser->setTabText(browser->indexOf(home), QApplication::translate("aplMainWindow", "Home", Q_NULLPTR));
        browser->setTabText(browser->indexOf(tab_2), QApplication::translate("aplMainWindow", "index", Q_NULLPTR));
        browser->setTabText(browser->indexOf(tab), QString());
        toolBar->setWindowTitle(QApplication::translate("aplMainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class aplMainWindow: public Ui_aplMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLMAINWINDOW_H
