[TOC]

 ## TabBar 带 '+' 扩展按钮的标签条

Qt原版的TabBar没有 '+' 扩展按钮，此处进行二次开发。

<p align="center"><img src="https://gitee.com/aiyudehua/drawing-bed/raw/master/https://gitee.com/aiyudehua/drawing-bed/tree/master/img/20210813224429.png" /> </p>             <p align="center">效果图</p>

<p align="center"><img src="https://gitee.com/aiyudehua/drawing-bed/raw/master/https://gitee.com/aiyudehua/drawing-bed/tree/master/img/20210813224453.png" /> </p>             <p align="center">Qt原版的标签条</p>

## 基本思路

- 继承QTabBar

- '+' 标签使用绝对布局的方式放入QTabBar

- 重写下列函数

  ```cpp
  virtual QSize sizeHint() const;
  virtual void resizeEvent(QResizeEvent *event);
  void tabLayoutChange();
  ```

## 实现细节

- 重写`virtual QSize sizeHint() const;`

  ```cpp
  // sizeHint的作用是给外部布局的一个提示(hint),将（+号）按钮的宽度算入其中
  QSize TabBar::sizeHint() const
  {
      QSize size = QTabBar::sizeHint();
      size.setWidth(size.width() + plusSize().width());
      return size;
  }
  ```

- 重写布局变更函数，让 '+' 按钮支持

  `virtual void resizeEvent(QResizeEvent *event);`
  `void tabLayoutChange();`

  ```cpp
  void TabBar::resizeEvent(QResizeEvent *event)
  {
      QTabBar::resizeEvent(event);// 发生布局变化时，先让QTabBar做出布局变化
      movePlusButton();           // 变化完毕，修改 '+' 的位置。因为我们用的绝对布局
  }
  
  void TabBar::tabLayoutChange()
  {
      QTabBar::tabLayoutChange(); // 发生布局变化时，先让QTabBar做出布局变化
      movePlusButton();           // 变化完毕，修改 '+' 的位置。因为我们用的绝对布局
  }
  ```

- '+' 标签移动思路

  ```cpp
  // 在 property("expending").toBool() 为真时 '+' 按钮失效！
  void TabBar::movePlusButton()
  {
      int x = 0;
      for(int i = 0; i < this->count(); i++)
      {
          x += tabRect(i).width();
      }
      int h = this->geometry().top();
      int w = this->width();
      if(x > w)   // 选项卡出现滚动条时
      {
          plusButton->move(w - 52, h);
      }
      else        // 无滚动条时
      {
          plusButton->move(x, h);
      }
  }
  ```

  

## 注意事项！（访问函数）

- '+' 标签按钮必须`手动开启`，且每次将它设置为QTabWidget的QTabBar时都必须重新开启一次。下边是这个功能的访问函数。

```cpp
bool plusVisiable();				// '+' 按钮是否可见
void setPlusVisiable(bool visiable);	// 设置 '+' 按钮可见性,[开启]
QSize plusSize() const;				// ‘+’ 按钮的大小
```

- '+' 按钮功能与expending功能冲突！一下函数使用时可能会影响'+'按钮的正常使用

```cpp
bool expanding();
void setExpanding(bool enable);
```

## 使用示例

```cpp
#include "tabbar.h"
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QTabWidget(parent)
{
    TabBar* bar = new TabBar(this);
    this->setTabBar(bar);
    for(int i = 0; i < 2; i++)
    {
        bar->addTab("123");
    }
    connect(bar, &TabBar::plusClicked, [=]
    {
        bar->addTab("aab");
    });
    // [重要]、[重要]、[重要]！手动显示
    bar->setPlusVisiable(true);
    this->setWindowTitle("'+'按钮示例");
}
```

