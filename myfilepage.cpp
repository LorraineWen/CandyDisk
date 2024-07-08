#include "myfilepage.h"
#include "ui_myfilepage.h"
#include<QPainter>
#include<QPixmap>
#include<QAction>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include<QJsonParseError>
#include <serverdatautil.h>
#include<QMessageBox>
MyFilePage::MyFilePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyFilePage)
{
    ui->setupUi(this);
    initFileList();
    initRightMenu();
    util=Util::get_instance();
    token=LoginToken::getInstance();
    manager=util->getmanger();
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
        blankMenu->exec(QCursor::pos());
    }
    else
    {
        iconMenu->exec(QCursor::pos());
    }

}
void MyFilePage::initRightMenu()
{
    //初始化右击图标时产生的菜单
    iconMenu=new RightMenu(this);
    downloadAction=new QAction("下载",this);
    shareAction=new QAction("分享",this);
   deleteAction=new QAction("删除",this);
   factorAction=new QAction("属性",this);
    iconMenu->addAction(downloadAction);
    iconMenu->addAction(shareAction);
    iconMenu->addAction(deleteAction);
    iconMenu->addAction(factorAction);
    blankMenu=new RightMenu(this);
    ascorderAction=new QAction("按下载量升序",this);
   descorderAction=new QAction("按下载降序排序",this);
    freshAction=new QAction("刷新",this);
   uploadAction=new QAction("上传",this);
    blankMenu->addAction(ascorderAction);
   blankMenu->addAction(descorderAction);
    blankMenu->addAction(uploadAction);
   blankMenu->addAction(freshAction);
    rightmenuconnect();
}
void MyFilePage::rightmenuconnect()
{
    connect(downloadAction,&QAction::triggered,this,[=](){
        qDebug()<<"下载文件";
    });
    connect(shareAction,&QAction::triggered,this,[=](){
        qDebug()<<"分享文件";
    });
    connect(deleteAction,&QAction::triggered,this,[=]()
            {
        qDebug()<<"删除文件";
    });
    connect(factorAction,&QAction::triggered,this,[=]()
            {
                qDebug()<<"文件属性";
            });
    connect(ascorderAction,&QAction::triggered,this,[=]()
            {
                qDebug()<<"升序排序";
        getUserFileCount(Asc);
            });
    connect(descorderAction,&QAction::triggered,this,[=]()
            {
                qDebug()<<"降序排序";
         getUserFileCount(Desc);
            });
    connect(freshAction,&QAction::triggered,this,[=]()
            {
                qDebug()<<"刷新文件";
        getUserFileCount(Normal);
            });
    connect(uploadAction,&QAction::triggered,this,[=]()
            {
                qDebug()<<"上传文件";
            });
}
void MyFilePage::getUserFileCount(MyFileDisplay cmd)
{
    filecount=0;
    QString ip=util->getConfValue("web_server","ip");
    QString port=util->getConfValue("web_server","port");
    QString user=token->getName();
    QString tok=token->getToken();
    QNetworkRequest request;
    QString url=QString("http://%1:%2/myfiles?cmd=count").arg(ip,port);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QJsonObject obj;
    obj.insert("user",user);
    obj.insert("token",tok);
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data=doc.toJson();
    QNetworkReply *reply=manager->post(request,data);
    if (reply->error() == QNetworkReply::NoError) {
        connect(reply,&QNetworkReply::readyRead,this,[=](){
            QByteArray rdata=reply->readAll();
            QStringList list=ServerDataUtil::getFileCount(rdata);
            if(!list.isEmpty())
                {
                QString code=list.at(0);
                if(code=="110")
                {
                    filecount=list.at(1).toInt();
                }
                else if(code=="111")
                {
                     QMessageBox::critical(this, "账号异常", "请重新登录");
                    this->hide();
                    emit loginagain();
                    return;
                }
            }
            if(filecount>0)
                {
                getUserFileList(cmd);
            }
            else
                {
                qDebug()<<"文件数为0";
            }
            reply->deleteLater();
       });
    } else {
        // 请求失败，输出错误信息
        qDebug() << "Request failed: " << reply->errorString();
    }
}
void  MyFilePage::getUserFileList(MyFileDisplay cmd)
{
    QString strcmd;
    if(cmd==Normal)strcmd="normal";
    else if(cmd==Desc)strcmd="pvdesc";
    else if(cmd==Asc)strcmd="pvasc";
    QString ip=util->getConfValue("web_server","ip");
    QString port=util->getConfValue("web_server","port");
    QString user=token->getName();
    QString tok=token->getToken();
    QNetworkRequest request;
    QString url=QString("http://%1:%2/myfiles?cmd=%3").arg(ip,port,strcmd);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QJsonObject obj;
    obj.insert("user",user);
    obj.insert("token",tok);
    obj.insert("start",0);
    obj.insert("count",filecount);
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data=doc.toJson();
    QNetworkReply *reply=manager->post(request,data);
    if (reply->error() == QNetworkReply::NoError) {
        connect(reply,&QNetworkReply::readyRead,this,[=](){
            QByteArray rdata=reply->readAll();
           filelist=ServerDataUtil::getFileInfo(rdata);
            if(!filelist.isEmpty())
            {
               for(int i=0;i<filelist.size();i++)
                {
                    qDebug()<<filelist[i]->fileName;
                }
            }
            reply->deleteLater();
        });
    } else {
        // 请求失败，输出错误信息
        qDebug() << "Request failed: " << reply->errorString();
    }
}

