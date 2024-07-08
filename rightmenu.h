#ifndef RIGHTMENU_H
#define RIGHTMENU_H
#include <QWidget>
#include <QMenu>
namespace Ui {
class RightMenu;
}

class RightMenu : public QMenu
{
    Q_OBJECT

public:
    explicit RightMenu(QWidget *parent = nullptr);
    ~RightMenu();

private:
    Ui::RightMenu *ui;
};

#endif // RIGHTMENU_H
