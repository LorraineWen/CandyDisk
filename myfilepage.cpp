#include "myfilepage.h"
#include "ui_myfilepage.h"
#include<QPainter>
#include<QPixmap>
MyFilePage::MyFilePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyFilePage)
{
    ui->setupUi(this);
    initFileList();
}

MyFilePage::~MyFilePage()
{
    delete ui;
}
void MyFilePage::initFileList()
{
    ui->fileList->setViewMode(QListView::IconMode);
    ui->fileList->setIconSize(QSize(80,80));
    ui->fileList->setGridSize(QSize(100,100));
    ui->fileList->setResizeMode(QListView::Adjust);
    ui->fileList->setMovement(QListView::Static);
    ui->fileList->addItem(new QListWidgetItem(QIcon(":/login/image/appicon.png"),"文件1"));
    ui->fileList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->fileList,&QListWidget::customContextMenuRequested,this,&MyFilePage::show_rightMenu);
}
void MyFilePage::show_rightMenu(const QPoint &pos)
{
    QListWidgetItem *item=ui->fileList->itemAt(pos);
    if(item==NULL)
    {
        qDebug()<<"右击了空处";
    }
    else
    {
        qDebug()<<"右击了图标";
    }

}
