#include "mainmenuui.h"
#include "ui_mainmenuui.h"
#include<QPainter>
#include<QPixmap>
#include<QDebug>
MainMenuUi::MainMenuUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenuUi)
{
    ui->setupUi(this);
    bg.load(":/main/image/menubackground3.jpg");
    menuconnect();
    //currentButton=ui->myfileButton;
    ui->myfileButton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
    /*
    smapper=new QSignalMapper(this);
    mapper.insert(ui->myfileButton->text(),ui->myfileButton);
    mapper.insert(ui->fileshareButton->text(),ui->fileshareButton);
    mapper.insert(ui->changeuserButton->text(),ui->changeuserButton);
    mapper.insert(ui->filedownloadbutton->text(),ui->filedownloadbutton);
    for(auto it=mapper.begin();it!=mapper.end();it++)
    {
        smapper->setMapping(it.value(),it.key());
        connect(it.value(),SIGNAL(clicked()),smapper,SLOT(map()));
    }
    connect(smapper,SIGNAL(mapped(QString)),this,SLOT(onMapperButtonClicked(QString)));
*/
}
/*
void MainMenuUi::defaultPage() {
    currentButton->setStyleSheet("color:black");
    currentButton = ui->myfileButton;
    ui->myfileButton->setStyleSheet("color:white");
}
*/
MainMenuUi::~MainMenuUi()
{
    delete ui;
}
void MainMenuUi::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),bg);
}
/*
void MainMenuUi::onMapperButtonClicked(QString text)
{
    qDebug()<<"hell哦“";
    QToolButton *btnTemp=nullptr;
    for(    auto it=mapper.begin();it!=mapper.end();it++)
    {
        if(it.key()==text)
        {
            btnTemp=it.value();break;
        }
    }
    if(btnTemp==currentButton)return;
    currentButton->setStyleSheet("color:black");
    currentButton=btnTemp;
    currentButton->setStyleSheet("color:wihte");
    if(text==ui->myfileButton->text())    emit show_myfilePage();
    else if(text==ui->fileshareButton->text())    emit show_sharefilePage();
    else if(text==ui->filedownloadbutton->text())    emit show_downloadfilePage();
    else if(text==ui->filetransportButton->text())    emit show_transportfilePage();
    else if(text==ui->changeuserButton->text())emit show_changeuserPage();
}
*/

void MainMenuUi::menuconnect()
{
    connect(ui->myfileButton, &QToolButton::clicked, this, [=](){
        emit show_myfilePage();

        ui->myfileButton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
        ui->fileshareButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filedownloadbutton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filetransportButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->changeuserButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
    });
    connect(ui->fileshareButton, &QToolButton::clicked, this, [=](){
        emit show_sharefilePage();

        ui->myfileButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->fileshareButton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
        ui->filedownloadbutton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filetransportButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->changeuserButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
    });
    connect(ui->filedownloadbutton, &QToolButton::clicked, this, [=](){
        emit show_downloadfilePage();

        ui->myfileButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->fileshareButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filedownloadbutton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
        ui->filetransportButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->changeuserButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
    });
    connect(ui->filetransportButton, &QToolButton::clicked, this, [=](){
        emit show_transportfilePage();

        ui->myfileButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->fileshareButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filedownloadbutton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filetransportButton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
        ui->changeuserButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
    });
    connect(ui->changeuserButton, &QToolButton::clicked, this, [=](){
        emit show_changeuserPage();
        ui->myfileButton->setStyleSheet("color:rgb(151, 116, 208);font: 700 10pt Microsoft YaHei UI");
        ui->fileshareButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filedownloadbutton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->filetransportButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
        ui->changeuserButton->setStyleSheet("color:black;font: 700 10pt Microsoft YaHei UI");
    });
}

