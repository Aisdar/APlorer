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

# QTableView实现详细信息方式显示文件

我们想实现类似于Windows资源管理器的显示效果：

![image-20210820202655608](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820202655608.png)

很容易的，我们想使用一个表格来实现这样的功能，借助Model/View的模式来实现：

![image-20210820202950448](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820202950448.png)

视图来接受并分发各种视图上的事件到各种操作上，合适的设置模型来让数据按照我们想要的方式排列。然后为了更好的将模型显示到视图上，我们额外使用代理来重绘界面的内容；同时代理将会处理视图上的各种修改将它们反馈到模型上，从而再次影响我们的视图。

我们选择模型为`QStandardItemModel`,因为它可以有更多的自由度；视图选择`QTableView`表格视图；代理则选择`QStyledItemDelegate`可以对每个Item进行处理。

## 获取系统的文件信息

我们借助qt的类来获取电脑文件系统的信息：

借助类QDir中的方法entryInfoList能获得当前文件夹下的所有文件的QFileInfo,这些QFileInfo对于我们构建文件信息的显示十分重要.

```c++
QFileInfoList QDir::entryInfoList(QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const
```

这个函数会基于QDir对象当前的`path`(不是`currentPath`)来进行遍历，其中第一个参数`QDir::Filters`枚举

![image-20210820225357029](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820225357029.png)

有这些值，我们根据需要选择`NoDotAndDotDot`,及不包含本文件夹和上一层文件夹。还有`AllEnties`包含所有文件夹，驱动和文件。

然后我们以E盘作为测试：

```c++
dir.setPath("E://");
for (auto x: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
    // 过滤选择不要上一级和本级目录
    qDebug() << x;
    /** 其他内容 **/
}
```

![image-20210820225833429](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820225833429.png)

能够顺利获取所有E盘下所有的文件的`QFileInfo`。

## Model的设计

数据模型的Table表现形式：

![image-20210820234746586](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210820234746586.png)

设置模型的代码：

```c++
/**模型定义**/
QStandardItemModel *model = new QStandardItemModel;

/**模型内容设置**/
QStandardItem* item = new QStandardItem; // 第一列需要较为复杂的item
int row = model->rowCount(); // 每次都是新增列，所以行数为rowCount
item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
model->setItem(row, 0, item); // 第一列文件名
model->setItem(row, 1, new QStandardItem(x.lastModified().toString("yyyy/M/d hh:m"))); // 第二列上次修改日期
model->setItem(row, 2, new QStandardItem(fileType(x))); // 第三列文件类型
model->setItem(row, 3, new QStandardItem(sizeFormat(x))); // 第四列大小
```

> 对于QStandardItemModel，每个格子都是一个QStandardItem，这个item中包含着不同的data（数据）供View来显示，一个item中可以包含很多data，这些data又对应不同的role（角色）。以QStandardItem的构造函数为例：
>
> ```c++
> QStandardItem(const QString &text)
> ```
>
> 它会将这个QString的内容也作为item的一种data进行存储，它对应的role为`Qt::DisplayRole`，在不设定代理时，view会使用这个字符作为显示的内容。我们也能自己对item的data进行设置，通过：
>
> ```c++
> void setData(const QVariant &value, int role = Qt::UserRole + 1)
> ```
>
> 我们可以将其他类型（可以转换为Variant）数据存到对应item中，然后设置role时，可以设置UserRole+i，i作为任意整数来取不同的对象来关联。然后设置好了对应data，我们还要在别的地方取出来，在类外获得某一个格子的方式更多是通过`QModelIndex`，我们可以通过行和列来确定某个模型的`ModelIndex`，我们也通过它来获得某个item的数据。
>
> ```c++
> QVariant QModelIndex::data(int role = Qt::DisplayRole) const
> ```
>
> 通过这个函数，我们来指定角色，就可以逆向获得model的数据，只要将数据转换为我们需要的类型即可。

这时候我们设置第一列数据为文件的绝对路径方便获取文件名和文件图标（顺便传递了是否为文件夹的bool参数，方便使用）；第二列数据为lastModify（上次修改日期），转为字符的函数转为我们需要的日期格式；第三列我们编写了fileType函数：

```c++
QString MainWindow::fileType(QFileInfo info)
{
    // 获得文件类型
    QFileIconProvider provider;
    QString type;
    if (provider.type(info) == "File Folder")
        // 文件夹直接替换内容
        type = "文件夹";
    else {
        // 其他替换掉为文件字样
        QString temp = provider.type(info);
        type = temp.replace("File", "文件");
    }
    return type;
}
```

利用`QFileProvider`类的接口，可以获得英文的类型名，这时候进行适当的替换；第四列我们设置文件的大小数据，`QFileInfo`类返回的size默认单位为B，类型为qint64，我们使用自己编写的sizeFormat函数来获得何时单位的字符串。

```c++
QString MainWindow::sizeFormat(QFileInfo info)
{
    // 获取文件大小合适的显示方式
    if (info.size() == 0)
        return "";
    else if (info.size() < 1024)
        return QString::number(info.size()) + "B";
    else if (info.size()/1024 < 1024)
        return QString::number(info.size()/1024) + "KB";
    else if (info.size()/(1024*1024) < 1024)
        return QString::number(info.size()/(1024*1024)) + "MB";
    else
        return QString::number(info.size()/(1024*1024)) + "GB";
}
```

这样Model的信息就设置好了，设置view的mode后就可以完成部分显示，除了文件名，因为文件名项的DisplayRole下的数据为空，我们还需要设计代理类来更好的显示。

```c++
 model = new QStandardItemModel(this);
ui->tableView->setModel(model);
```



## 代理类的设计

> 代理有很多虚函数需要我们覆写来适应我们的要求:
>
> ```c++
> QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
> void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const 
> void setEditorData(QWidget *editor, const QModelIndex &index) const 
> void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
> QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const 
> void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
> ```
>
> 1. `createEditor`可以为当前index的view创建一个编辑器，这个编辑器通常用为`QLineEdit`，`QPlainTextEdit`，`QSpinBox`等等输入空间或者自己编写的输入空间类，每次双击都会激活这个编辑器，然我们来编辑编辑器上的数据，然后我们可以通过相应函数将这些改变反馈到Model上，完成Model中数据的更新。
> 2. `paint`为绘制每一个View的方式，一般来说编辑器默认情况下是不显示出来的，所以需要我们把数据以绘制的形式显示出来。
> 3. `setEditorData`设置编辑器数据。
> 4. `setModeData`由编辑器的数据反馈到Model的数据上。
> 5. `SizeHint`返回控件的推荐尺寸，在M/V模式中，我们不能通过简单的设置View的属性来改变显示的尺寸，需要通过`SizeHint`来设置合适的尺寸，然后借助view的`resizeToContent`方法来适应到我们需要的大小。
> 6. `updateEditorGeometry`更新编辑器的位置信息。

了解到代理类中我们需要覆写的函数后，我们了解View设置代理的模式，对于`QTableView`，有这样三个方式：

```c++
setItemDelegate(QAbstractItemDelegate *delegate); // 全局设置
setItemDelegateForRow(int row, QAbstractItemDelegate *delegate);// 行设置
setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate); // 列设置
```

对于详细信息，我们可以使用列设置的方式，根据需要我们编写两个代理类即可。

### 文件名代理类具体实现

1. 编辑器创建

   ```c++
   1. QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
      {
          QLineEdit *editor = new QLineEdit(parent); // 新建一个LineEdit作为编辑器，一定设置好父类，不然显示位置错误
          // 从ModelIndex中获取Model中文件完整路径数据
          QString fileName = index.data(Qt::UserRole+1).value<QString>(); 
          QFileInfo info(fileName); // 根据路径获得文件的FileInfo
          editor->setText(info.fileName()); // 设置编辑器的数据
          connect(editor, &QLineEdit::editingFinished, [=](){
              // 编辑器回车完成编辑后触发
              editor->hide(); // 编辑器隐藏
          });
          return editor; // 需要返回编辑器的指针
      }
   ```

2. 绘制

   ```c++
   void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
   {
       QRect rect = option.rect; // 系统的矩形
       QFileIconProvider provider;  // 获得系统图标
       QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
       QFileInfo info(fileName); // 获得对应路径下的文件信息
       bool isDir = index.data(Qt::UserRole+2).value<bool>(); // 通过是否为文件夹获得对应图标
       QIcon icon;
       if (isDir) {
           // 获得图标，文件夹
           icon = provider.icon(QFileIconProvider::Folder);
       } else {
           // 获得图标各种类型的文件
           icon = provider.icon(info);
       }
       icon.paint(painter, rect, Qt::AlignLeft); // 在左侧绘制图标，宽度大概为30
       // 设置文字略缩样式
       QFontMetrics metrics(painter->font());
       QString text = info.fileName();
       if(metrics.width(text) > rect.width()-40)
       {
           // 略缩字样如果大于可供显示的尺寸（rect.width()-40)文字略缩
           text = metrics.elidedText(text, Qt::ElideRight, rect.width()-40);
       }
       painter->drawText(rect.adjusted(+30, 0, 0, 0), Qt::AlignVCenter|Qt::AlignLeft, text); // 画出文件名的文字
   }
   ```

3. 设置模型数据

   这里重命名需要完成的路径名不然文件会被更改位置，用`absoluteDir`获得文件的文件夹，然后加上新的文件名。

   ```c++
   void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
   {
       QStandardItemModel *smodel = static_cast<QStandardItemModel *>(model);
       QLineEdit *editor1 = static_cast<QLineEdit *>(editor); // 获得原编辑器
       QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
       QFile file(fileName);
       QFileInfo x(file);
       if (file.rename(x.absoluteDir().path() + "/" + editor1->text())) {
           // 直接重命名文件
           x.setFile(file);
           QStandardItem *item = new QStandardItem; // 新建模型的Item重设显示信息
           item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
           item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
           smodel->setItem(index.row(), 0, item); // 重设item
       }
   }
   ```

4. 尺寸数据

   ```c++
   QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
   {
       QSize size = option.rect.size(); // 获得原编辑器的尺寸
       size.setWidth(size.width()+500); // 宽度增加500
       return size;
   }
   ```

5. 编辑器位置

   ```c++
   void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
   {
       editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0)); // 编辑器只占右边部分
   }
   ```

这样代理就设置好了，效果大概如下：

![image-20210829220739233](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210829220739233.png)

在其他函数中的设定如下：

```c++
MyDelegate *delegate = new MyDelegate(this);
ui->tableView->setItemDelegateForColumn(0, delegate);
```

### 其他形式代理设计

```c++
QWidget *DtailDelegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr; // 返回空指针，这个项目不可编辑
}

void DtailDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 绘制略缩文字
    QRect rect = option.rect;
    QString text = index.data().toString();
    QFontMetrics metrics(painter->font());
    if(metrics.width(text) > rect.width())
    {
        text = metrics.elidedText(text, Qt::ElideRight, rect.width());
    }
    painter->drawText(option.rect, text, Qt::AlignVCenter|Qt::AlignLeft);
}

QSize DtailDelegate2::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, option.rect.height()); // 固定宽度
}
```

这样形式的代理设定好了后，其他`文件类型`、`修改时间`和`大小`将被正常显示，而且是不可修改的状态。

![image-20210901223755520](https://gitee.com/chenyuyu118/project-f/raw/master/image/image-20210901223755520.png)



