#include "mainmenuui.h"
#include "ui_mainmenuui.h"
#include<QPainter>
#include<QPixmap>
MainMenuUi::MainMenuUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenuUi)
{
    ui->setupUi(this);
    bg.load(":/main/image/menubackground3.jpg");
}

MainMenuUi::~MainMenuUi()
{
    delete ui;
}
void MainMenuUi::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),bg);
}
