# QToolButton下拉菜单实现

我们想实现这样的按钮：

![image-20210807213240095](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210807213240095.png)

使用QToolButton实现：

```c++
void aplMainWindow::setMenus()
{
   QMenu *menu = new QMenu(this); // 创建一个下拉菜单
   menu->addAction(ui->actionforward); // 添加菜单中内容

   ui->btn_backward->setPopupMode(QToolButton::MenuButtonPopup); // 向ui中的按钮设置弹出模式
   ui->btn_backward->setToolButtonStyle(Qt::ToolButtonIconOnly); // 按钮只显示图标
   ui->btn_backward->setMenu(backwardMenu); // 设置按钮对应的菜单
}
```

这会使得菜单成这样：

![image-20210807215531182](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210807215531182.png)

但是对于回退和前进按钮需要保存访问文件夹的路径名和执行对应操作，我们可以通过在action的triggered槽函数中添加这些代码：

```c++
    QMenu *menu = ui->btn_backward->menu(); // 获取某个QToolButton的下拉菜单指针
    menu->addAction("1111"); // 向这个菜单中添加对应Action
```

这样菜单就可以根据需要添加QAction。

![image-20210807221454921](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210807221454921.png)

# QTableView实现显示文件系统

我们想实现类似于Windows资源管理器的显示效果：

![image-20210820202655608](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820202655608.png)

很容易的，我们想使用一个表格来实现这样的功能，借助Model/View的模式来实现：

![image-20210820202950448](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820202950448.png)

视图来接受并分发各种视图上的事件到各种操作上，合适的设置模型来让数据按照我们想要的方式排列。然后为了更好的将模型显示到视图上，我们额外使用代理来重绘界面的内容；同时代理将会处理视图上的各种修改将它们反馈到模型上，从而再次影响我们的视图。

我们选择模型为`QStandardItemModel`,因为它可以有更多的自由度；视图选择`QTableView`表格视图；代理则选择`QStyledItemDelegate`可以对每个Item进行处理。

## 获取系统的文件信息



