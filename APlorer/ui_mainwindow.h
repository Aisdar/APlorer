/********************************************************************************
** Form generated from reading UI file 'aplmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVersion;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QFrame *line;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1057, 542);
        actionVersion = new QAction(MainWindow);
        actionVersion->setObjectName(QStringLiteral("actionVersion"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(3, 3, 3, 3);
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        line = new QFrame(widget_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_4->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_4->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_4->addWidget(pushButton_6);


        gridLayout->addWidget(widget_3, 0, 0, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 3, 3, 3);
        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(140);
        sizePolicy.setVerticalStretch(25);
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMinimumSize(QSize(140, 25));

        horizontalLayout_3->addWidget(lineEdit_2);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(widget);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        treeView->setMinimumSize(QSize(350, 0));
        treeView->setMaximumSize(QSize(350, 16777215));

        horizontalLayout_2->addWidget(treeView);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(tab);
        listView->setObjectName(QStringLiteral("listView"));

        horizontalLayout->addWidget(listView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout_2->addWidget(tabWidget);


        gridLayout->addWidget(widget, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1057, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionVersion);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "APlorer", Q_NULLPTR));
        actionVersion->setText(QApplication::translate("MainWindow", "Version", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\211\215\350\277\233", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\220\216\351\200\200", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\351\241\266\345\261\202", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "333", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\265\213\350\257\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
