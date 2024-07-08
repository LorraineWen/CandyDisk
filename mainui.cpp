#include "mainui.h"
#include "ui_mainui.h"
#include<QPainter>
MainUi::MainUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainUi)
{
    ui->setupUi(this);
     QIcon icon(":/login/image/appicon.png");
     this->setWindowIcon(icon);
     mainconnect();
}

MainUi::~MainUi()
{
    delete ui;
}
void MainUi::mainconnect()
{
    //页面切换槽
    connect(ui->MainMenu,&MainMenuUi::show_myfilePage,this,[=](){
        ui->stackedWidget->setCurrentWidget(ui->myfilePage);
    });
    connect(ui->MainMenu,&MainMenuUi::show_sharefilePage,this,[=]()
            {
         ui->stackedWidget->setCurrentWidget(ui->sharefilePage);
    });
    connect(ui->MainMenu,&MainMenuUi::show_downloadfilePage,this,[=]{
         ui->stackedWidget->setCurrentWidget(ui->downloadPage);
    });
    connect(ui->MainMenu,&MainMenuUi::show_transportfilePage,this,[=]{
         ui->stackedWidget->setCurrentWidget(ui->transportPage);
    });
    connect(ui->MainMenu,&MainMenuUi::show_changeuserPage,this,[=]{
        this->hide();
        emit show_loginPage();
    });
}
