#include "rightmenu.h"
#include "ui_rightmenu.h"

RightMenu::RightMenu(QWidget *parent)
    : QMenu(parent)
    , ui(new Ui::RightMenu)
{
    QString styleSheet = R"(
    QMenu {
        background-color: rgb(85, 170, 255);
        font: 700 13pt Comic Sans MS;
        color: rgb(255, 255, 255);
    }
    QMenu::item {
 min-width: 50px; /* 设置固定宽度，根据需要调整具体数值 */
        max-width: 150px; /* 设置最大宽度，确保固定宽度 */
        border-bottom: 2px solid black;
        padding-bottom: 4px; /* 调整间隔线和文本之间的距离 */
        padding-top: 4px; /* 调整文本和上方边框之间的距禿 */
text-align:center;
    }
)";
    this->setStyleSheet(styleSheet);
    //this->setStyleSheet("background-color: rgb(85, 170, 255);font: 700 13pt Comic Sans MS;color: rgb(255, 255, 255);");
}

RightMenu::~RightMenu()
{
    delete ui;
}
