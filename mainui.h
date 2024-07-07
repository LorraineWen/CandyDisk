#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>

namespace Ui {
class MainUi;
}

class MainUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainUi(QWidget *parent = nullptr);
    ~MainUi();

private:
    Ui::MainUi *ui;
    void paintEvent(QPaintEvent *event);
    QPixmap bg;//将bg作为成员，变量，这样每次鼠标放大和缩小窗口就不用每次都加载一次图片了，只要在构造函数里面加载一次就够了，减少卡顿
};

#endif // MAINUI_H
