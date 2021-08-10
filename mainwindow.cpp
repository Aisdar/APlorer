#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")

#include <QCompleter>
#include <QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLineEdit* lineEdit = new QLineEdit(this);
    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta" << "小姐姐.mp4" << "大姐姐.mp3"
             << "啦啦啦" << "中姐姐.mp3";
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setFilterMode(Qt::MatchContains);
//      QCompleter::InlineCompletion；
//      QCompleter::PopupCompletion；
//      QCompleter::UnfilteredPopupCompletion；

    lineEdit->setCompleter(completer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

