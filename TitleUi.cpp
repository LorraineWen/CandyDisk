#include "TitleUi.h"
#include "ui_TitleUi.h"
#include<QPainter>
TitleUi::TitleUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TitleUi)
{
    ui->setupUi(this);
    ui->logo->setPixmap(QPixmap(":/login/image/logoicon.ico").scaled(40,40));
}

TitleUi::~TitleUi()
{
    delete ui;
}
void TitleUi::on_tosetbutton_clicked()
{
     emit show_setpage();
}


void TitleUi::on_tologbutton_clicked()
{
    emit show_logpage();
}


void TitleUi::on_toregisterbutton_clicked()
{
    emit show_registerpage();
}

