#include "mainui.h"
#include "ui_mainui.h"
#include<QPainter>
MainUi::MainUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainUi)
{
     bg.load(":/main/image/background2.jpg");
    ui->setupUi(this);
     QIcon icon(":/login/image/appicon.png");
     this->setWindowIcon(icon);
}

MainUi::~MainUi()
{
    delete ui;
}
void MainUi::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),bg);
}
