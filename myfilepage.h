#ifndef MYFILEPAGE_H
#define MYFILEPAGE_H

#include <QWidget>

namespace Ui {
class MyFilePage;
}

class MyFilePage : public QWidget
{
    Q_OBJECT

public:
    explicit MyFilePage(QWidget *parent = nullptr);
    ~MyFilePage();

private:
    Ui::MyFilePage *ui;
    void initFileList();
private slots:
    void show_rightMenu(const QPoint &pos);
};

#endif // MYFILEPAGE_H
