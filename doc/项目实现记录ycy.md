# QToolButton下拉菜单实现

我们想实现这样的按钮：

![image-20210807213240095](E:\APlorer\doc\img\image-20210807213240095.png)

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

![image-20210807215531182](E:\APlorer\doc\img\image-20210807215531182.png)

但是对于回退和前进按钮需要保存访问文件夹的路径名和执行对应操作，我们可以通过在action的triggered槽函数中添加这些代码：

```c++
    QMenu *menu = ui->btn_backward->menu(); // 获取某个QToolButton的下拉菜单指针
    menu->addAction("1111"); // 向这个菜单中添加对应Action
```

这样菜单就可以根据需要添加QAction。

![image-20210807221454921](E:\APlorer\doc\img\image-20210807221454921.png)

# 窗体控件大小可调节实现

