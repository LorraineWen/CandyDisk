#include "filefactorui.h"
#include "ui_filefactorui.h"
#include <QPainter>
FileFactorUi::FileFactorUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileFactorUi)
{
    ui->setupUi(this);
    QString style1="color:rgb(135, 57, 193);font: 700 14pt Microsoft YaHei UI;text-decoration: underline;";
     QString style2="font: 700 14pt Microsoft YaHei UI;";
    QIcon icon(":/login/image/appicon.png");
    this->setWindowIcon(icon);
    bg.load(":/main/image/menubackground.jpg");
    ui->label->setStyleSheet(style2);
    ui->label_2->setStyleSheet(style2);
    ui->label_3->setStyleSheet(style2);
    ui->label_4->setStyleSheet(style2);
    ui->label_5->setStyleSheet(style2);
    ui->label_7->setStyleSheet(style2);
    ui->filename->setStyleSheet(style1);
    ui->filesize->setStyleSheet(style1);
    ui->status->setStyleSheet(style1);
    ui->uploader->setStyleSheet(style1);
    ui->uploadtime->setStyleSheet(style1);
    ui->downloadtime->setStyleSheet(style1);
}

FileFactorUi::~FileFactorUi()
{
    delete ui;
}
void FileFactorUi::setFileFactor(File*file)
{
int size = file->size;
    //1kb = 1024个字节
    //展示给用户看的是KB,MB
    if (size>=1024 && size < 1024*1024) {
        ui->filesize->setText(QString("%1 KB").arg(size/1024.0));
    }
    else {
        ui->filesize->setText(QString("%1 MB").arg(size/1024.0/1024.0));
    }
    if (file->shareStatus == 0) {
        ui->status->setText("没有分享");
    } else if (file->shareStatus == 1) {
        ui->status->setText("已经分享");
    }
    ui->uploadtime->setText(file->createTime);
    ui->uploader->setText(file->user);
    ui->downloadtime->setText(QString("被下载 %1 次").arg(file->pv));
    ui->filename->setText(file->fileName);
    this->setWindowTitle("文件"+file->fileName+"的属性");
}
void FileFactorUi::paintEvent(QPaintEvent*event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),bg);
}
