```cpp
// 编辑人: 陈一鸣
// 最后编辑时间: 2021/8/13
```

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

- 定义 '+' 按钮大小

  ```cpp
  // TabBar.h
  #define PLUS_SIZE QSize(20, 20)
  // 返回 '+'的大小
  ```

  ```cpp
  // TabBar.cpp
  TabBar::TabBar(QWidget *parent)
      : QTabBar(parent)
  {
      plusButton = new QPushButton("+", this);
      plusButton->setFixedSize(PLUS_SIZE);   // QSize(20, 20),但是按钮的大小比这个大！
      connect(plusButton, &QPushButton::clicked, this, &TabBar::plusClicked); // '+' 信号
  }
  
  QSize TabBar::plusSize() const
  {
      return plusButton->size();   // QSize(20, 20)
  }
  ```

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

- '+' 标签移动思路: 遍历标签获得宽度，将 '+' 标签采用绝对布局放在最后一个标签右边。由于重写过sizeHint()，实际整个标签控件比父类要宽度 20 px.

  `void movePlusButton()`
  
  ```cpp
  // '+' 按钮 关键函数
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
          if(expanding())     // 解决与 expanding冲突
              x = x - 20;
          plusButton->move(x, h);
      }
  }
  ```
  
  

## 注意事项！（访问函数）

- '+' 标签按钮必须`手动开启`，且每次将它设置为QTabWidget的QTabBar时都必须重新开启一次。下边是这个功能的访问函数。

```cpp
bool plusVisiable();				// '+' 按钮是否可见
void setPlusVisiable(bool visiable);		// 设置 '+' 按钮可见性
QSize plusSize() const;				// ‘+’ 按钮的大小
void setPlusOnTabRight(bool isRight);		// 设置 ‘+’ 按钮在标签右侧，默认是在标签上的！
```

- '+' 按钮功能与expending功能冲突！以下函数使用时可能会影响'+'按钮的正常使用，具体影响在下边有提到（待优化）

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
    // [重要]、[重要]、[重要]！手动修改它的位置在标签右侧！！
    bar->setPlusOnTabRight(true);
    this->setWindowTitle("'+'按钮示例");
}
```

## 待优化

```cpp
//    bar->setPlusOnTabRight(true);	// 代码中如果不加这句
```

<p align="center"><img src="https://gitee.com/aiyudehua/drawing-bed/raw/master/https://gitee.com/aiyudehua/drawing-bed/tree/master/img/20210813231716.png" /> </p>             <p align="center">不开启'+'标签右侧显示</p>

有点丑
