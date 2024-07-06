#include "TitleUi.h"
#include "ui_TitleUi.h"

TitleUi::TitleUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TitleUi)
{
    ui->setupUi(this);
    ui->logo->setPixmap(QPixmap(":/image/logoicon.ico").scaled(40,40));
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


void TitleUi::on_toolButton_clicked()
{
    emit show_logpage();
}


void TitleUi::on_toolButton_2_clicked()
{
    emit show_registerpage();
}


void TitleUi::on_toolButton_3_clicked()
{
    emit show_setpage();
}

