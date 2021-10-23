#include "customstyle.h"


QSize CustomStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    // 重新修改TabBar的大小
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
        s.rheight() = 30;
        s.rwidth() = 90;
    }
    return s;
}

void CustomStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        // 重绘标签
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            QRect allRect = tab->rect; // 获取标签的对应矩形
            allRect.setWidth(allRect.width()-5); // 矩形改变大小
            // 根据状态重绘标签
            if (tab->state & QStyle::State_Selected)
            {
                //选中状态
                //save用以保护坐标，restore用来退出状态
                painter->save();
                painter->setBrush(QBrush(0xeed7c1));
                //矩形
                painter->drawRect(allRect);
                painter->restore();
            }
            else if(tab->state & QStyle::State_MouseOver)
            {
                //hover状态
                painter->save();
                painter->setBrush(QBrush(0xeed7c1));
                //painter->drawRoundedRect(tab->rect, 8, 8);
                painter->drawRect(allRect);
                painter->restore();
            }
            else
            {
                painter->save();
                painter->setBrush(QBrush(0x78aadc));
                //painter->drawRoundedRect(tab->rect 8, 8);
                painter->drawRect(allRect);
                painter->restore();
            }
            // 重绘字体
            QTextOption option2;
            option2.setAlignment(Qt::AlignCenter);
            painter->setFont(QFont("楷体", 10));
            painter->drawText(allRect.adjusted(0, 0, -10, 0), tab->text, option2);
            }
    }
    if (element == CE_TabBarTab) {
        // tab使用默认绘制
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

