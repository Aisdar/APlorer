#include "aplmainwindow.h"
#include "mytabwidget.h"
#include "ui_aplmainwindow.h"
#include "driverwidget.h"
#include "customstyle.h"
#include "tabbar.h"
#include "SearchWindow.h"
#include "everythingutil.h"

#include <QSettings>
#include <QFileSystemModel>
#include <QDebug>
#include <QMimeDatabase>
#include <QPushButton>
#include <QTableView>
#include <QApplication>
#include <QTranslator>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QDateTime>
#include <QFileIconProvider>

aplMainWindow::aplMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("APlorer"); // 设置标题

    initToolBar(); // 初始化工具栏
    QWidget *homePage = new QWidget(ui->brower);
    ui->brower->initHomeTab(homePage); // 初始化浏览窗口的HomePage
    ui->brower->addTab(homePage, QIcon(":/icon/default theme/home-.png"), "Home"); // 添加一个页面

    loadSettings();
    EveryThingUtil::openEverything();
    searchWindow = new SearchWindow(this);

    searchWindow->setHidden(true);
    connect(btn_hide, &QToolButton::clicked, this, &aplMainWindow::slt_hidePreview);
}

aplMainWindow::~aplMainWindow()
{
    delete ui;
}

void aplMainWindow::init()
{
    // 文件模型M
    m_model = new QFileSystemModel;
    m_model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    // [重要]设置根目录，直接初始化了磁盘索引信息到M中
    m_model->setRootPath("c:");
    // 设置模型
    ui->directoryTree->setModel(m_model);

    for (int i = 1; i < 4; ++i)
        ui->directoryTree->setColumnHidden(i, true);

}

QFileSystemModel *aplMainWindow::fileModel()
{
    return m_model;
}

void aplMainWindow::copy(aplMainWindow *oldApl)
{
    if(oldApl){
        QFileSystemModel* model = oldApl->fileModel();
        if(model){
            this->ui->directoryTree->setModel(model);
        }
    }
    else{
        qDebug() << "aplMainWindow::aplMainWindow(QWidget *, aplMainWindow *)->新窗口的参数aplMainWindow * 为空指针";\
    }
}

void aplMainWindow::setToolButtonActions(QAction *forward, QAction *backward)
{
    // 设置按钮对应Action
    ui->btn_backward->setDefaultAction(backward);
    ui->btn_forward->setDefaultAction(forward);
}

void aplMainWindow::setLayoutMenu(QMenu *menu)
{
    btn_layout->setMenu(menu);
}

void aplMainWindow::setHistoryMenu(QMenu *menu)
{
    ui->btn_backspace->setMenu(menu);
}

void aplMainWindow::setPathBox(QString path)
{
    int index = ui->pathBox->findText(path);
    ui->pathBox->setCurrentIndex(index);
}

void aplMainWindow::addPathBox(QString path)
{
    ui->pathBox->addItem(path);
    ui->pathBox->setCurrentText(path);
}

void aplMainWindow::setRankMenu(QMenu *menu)
{
    btn_rank->setMenu(menu);
}

void aplMainWindow::setPreviewLabel(QModelIndex index)
{
    QString absolutePath = index.data(Qt::UserRole+1).toString();
    setPreviewLabel(absolutePath);
}

void aplMainWindow::setPreviewLabel(QString path)
{
    QMimeDatabase db;
    QString type = db.mimeTypeForUrl(path).name();
    if (type.contains("text")) {
        QFile previewfile(path);
        ui->previewLabel->setAlignment(Qt::AlignLeft);
        if (!previewfile.open(QIODevice::ReadOnly)) {
            ui->previewLabel->setText("open failed");
        } else {
            ui->previewLabel->setText(previewfile.readAll());
        }
    } else if (type.contains("image")) {
        QPixmap pixmap(path);     
        if (ui->previewLabel)
        {
            if (!this->searchWindow->isHidden())
                this->searchWindow->setHidden(true);
            ui->previewLabel->setAlignment(Qt::AlignCenter);
            ui->previewLabel->setPixmap(pixmap.scaled(ui->previewLabel->size(),
                                                      Qt::KeepAspectRatio,
                                                      Qt::SmoothTransformation));
        }
    }
}

void aplMainWindow::setStatuBarString(QString text)
{
    if (!label_statuBar)
        label_statuBar = new QLabel;
    label_statuBar->setText(text);
    ui->statusbar->addWidget(label_statuBar);
}

void aplMainWindow::setSearchContent(QString text)
{
    this->searchWindow->lineEdit_textChanged(text);
    this->on_actionSearch_triggered();
}

void aplMainWindow::setSearchWindowHidden(bool hide)
{
    this->searchWindow->setHidden(hide);
}

void aplMainWindow::setTreeView(QString path)
{
    ui->directoryTree->setCurrentPage(path);
}

void aplMainWindow::initToolBar()
{
    // 初始化工具栏
    // 一个空白
    QWidget *emptyWidget1 = new QWidget(this);
    emptyWidget1->setFixedSize(60, 35);
    ui->toolBar->insertWidget(ui->actionsetting, emptyWidget1);

    // 历史按钮
    ui->btn_backspace->setIcon(QIcon(":/icon/default theme/history.png"));
    ui->btn_backspace->setPopupMode(QToolButton::InstantPopup);

    // 布局按钮和菜单
    btn_layout = new QToolButton(this);
    btn_layout->setIcon(QIcon(":/icon//default theme/grid.png"));
    btn_layout->setText("布局");
    btn_layout->setPopupMode(QToolButton::InstantPopup);
    btn_layout->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->toolBar->insertWidget(ui->actionsetting, btn_layout);

    // 添加设置按钮
    QWidget *emptyWidget2 = new QWidget(this);
    emptyWidget2->setFixedSize(200, 35);
    ui->toolBar->insertWidget(ui->actionsetting, emptyWidget2);

    // 添加空白
    QWidget *emptyWidget3 = new QWidget(this);
    emptyWidget3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QAction *sp = ui->toolBar->addSeparator();
    ui->toolBar->insertWidget(sp, emptyWidget3);

    // 预览栏按钮
    btn_hide = new QToolButton(this);
    btn_hide->setIcon(QIcon(":/icon/default theme/eye.png"));
    btn_hide->setText("显示预览栏");
    btn_hide->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn_hide->setCheckable(true);
    btn_hide->setChecked(true);
    ui->toolBar->addWidget(btn_hide);
}

void aplMainWindow::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    if (!this->searchWindow->isHidden())
        on_actionSearch_triggered();
}

void aplMainWindow::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);
    if (!searchWindow->isHidden()) {
        this->on_actionSearch_triggered();
    }
}

void aplMainWindow::on_actionhome_triggered()
{
    this->searchWindow->hide();
    // 回到主页
    int index = ui->brower->currentIndex();
    ui->brower->removeTab(index);
    QWidget* homePage = new QWidget;
    ui->brower->initHomeTab(homePage);
    ui->brower->insertTab(index, homePage, QIcon(":/icon/default theme/home-.png"), "Home");
    ui->brower->setCurrentIndex(index);
}

void aplMainWindow::on_actionSearch_triggered()
{
    QRect rect = ui->brower->currentWidget()->rect();
    QPoint p = ui->brower->currentWidget()->mapToGlobal(QPoint(0, 0));
    rect.setTopLeft(this->mapFromGlobal(p));
    rect.setHeight(ui->brower->height());
    rect.setWidth(ui->brower->width());
    searchWindow->setGeometry(rect);
    searchWindow->show();
}

void aplMainWindow::on_pathBox_currentIndexChanged(const QString &arg1)
{
    this->searchWindow->hide();
    QFileInfo info(arg1);
    if (info.isDir())
    {
        MyTableView *view = static_cast<MyTableView *>(ui->brower->currentWidget()->findChild<MyTableView *>());
        if (view) {
            view->setCurrentPage(arg1, view->getCurrentMode(), false);
        }
        else {
            int index = ui->brower->currentIndex();
            ui->brower->removeTab(index);
            QWidget *w = new QWidget;
            ui->brower->initPageTab(arg1, w);
            ui->brower->insertTab(index, w, arg1);
            ui->brower->setCurrentIndex(index);
        }
    }
}

void aplMainWindow::on_directoryTree_clicked(const QModelIndex &index)
{
    this->searchWindow->hide();
    QString filePath = m_model->filePath(index);
    MyTableView *view = ui->brower->currentWidget()->findChild<MyTableView *>();
    if (view) {
        view->setCurrentPage(filePath, view->getCurrentMode(), true);
    } else {
        int index = ui->brower->currentIndex();
        ui->brower->removeTab(index);
        QWidget *w = new QWidget;
        ui->brower->initPageTab(filePath, w);
        ui->brower->insertTab(index, w, filePath);
        ui->brower->setCurrentIndex(index);
    }
}

void aplMainWindow::slt_hidePreview()
{
    if (btn_hide->isChecked()) {
        ui->previewLabel->setHidden(false);
    } else {
        ui->previewLabel->setHidden(true);
    }
    resize(this->width(), this->height());
}


void aplMainWindow::on_searchBox_textChanged(const QString &arg1)
{
    this->searchWindow->lineEdit_textChanged(arg1);
    this->on_actionSearch_triggered();
}


void aplMainWindow::on_btn_backward_clicked()
{
    if (!this->searchWindow->isHidden()) {
        this->searchWindow->setHidden(true);
    }
}


void aplMainWindow::loadSettings() {
    QSettings set("APlore", "settings");
    QRect r =  set.value("rect").toRect();
    bool hide = set.value("preView").toBool();
    if (!r.isEmpty())
    {
        this->setGeometry(r);
        this->btn_hide->setChecked(!hide);
    }
}

void aplMainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    QSettings set("APlore", "settings");
    set.setValue("rect", this->rect());
    set.setValue("preView", ui->previewLabel->isHidden());
}

