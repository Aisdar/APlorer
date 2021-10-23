#include "tabbar.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QDebug>

TabBar::TabBar(QWidget *parent)
    : QTabBar(parent)
{
    plusButton = new QPushButton("+", this);
    plusButton->setFixedSize(PLUS_SIZE);   // QSize(20, 20),但是按钮的大小比这个大！
    connect(plusButton, &QPushButton::clicked, this, &TabBar::plusClicked); // '+' 信号
}

// sizeHint的作用是给外部布局的一个提示(hint),将（+号）按钮的宽度算入其中
QSize TabBar::sizeHint() const
{
    QSize size = QTabBar::sizeHint();
    size.setWidth(size.width() + plusSize().width());
    return size;
}

// 返回 '+'的大小
QSize TabBar::plusSize() const
{
    return plusButton->size();   // QSize(20, 20)
}

bool TabBar::plusVisiable()
{
    return plusButton->isVisible();
}

void TabBar::setPlusVisiable(bool visiable)
{
    plusButton->setVisible(visiable);
}

// 没错，'+' 按钮依赖于别的属性，必须设置expanding属性为false
void TabBar::setPlusOnTabRight(bool isRight)
{
    setExpanding(!isRight);
}


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
