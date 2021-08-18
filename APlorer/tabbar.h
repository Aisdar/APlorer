#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>

#define PLUS_SIZE QSize(30, 30)

class QPushButton;

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize plusSize() const;
    bool plusVisiable();
    void setPlusVisiable(bool visiable);
    void setPlusOnTabRight(bool isRight);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void tabLayoutChange() override;

private:
    QPushButton* plusButton;

private slots:
    void movePlusButton();

signals:
    void plusClicked();

};

#endif // TABBAR_H
