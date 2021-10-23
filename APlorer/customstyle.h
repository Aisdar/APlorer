#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H

#include <QProxyStyle>
#include <QObject>
#include <QWidget>
#include <QSize>
#include <QStyleOption>
#include <QDebug>
#include <QPainter>


class CustomStyle : public QProxyStyle
{
    Q_OBJECT
public:
    CustomStyle(QStyle *style = nullptr);
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const override;
};

#endif // CUSTOMSTYLE_H
