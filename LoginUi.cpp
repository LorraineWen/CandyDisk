#include "LoginUi.h"
#include "ui_LoginUi.h"
#include <QPushButton>
#include <QRegularExpression>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonParseError>
#include "des.h"

LoginUi::LoginUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    QIcon icon(":/login/image/appicon.png");
    this->setWindowIcon(icon);
    bg.load (":/login/image/background1.jpg");
     mainui=new MainUi();
    myfilepage=new MyFilePage();
    loginconnect();
    util=Util::get_instance();
    manager=util->getmanger();
    ltoken=LoginToken::getInstance();
    readConf();
    server_set();
}

LoginUi::~LoginUi()
{
    delete ui;
}
void LoginUi::loginconnect()
{
    connect(ui->titlewidget,&TitleUi::show_setpage,this,&LoginUi::on_tosetpage);
    connect(ui->titlewidget,&TitleUi::show_logpage,this,&LoginUi::on_tologbutton_2_clicked);
    connect(ui->titlewidget,&TitleUi::show_registerpage,this,&LoginUi::on_registerbutton_4_clicked);
    connect(mainui,&MainUi::show_loginPage,this,&LoginUi::set_loginPage);
    connect(myfilepage,&MyFilePage::loginagain,this,&LoginUi::set_loginPage);
}

void LoginUi::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),bg);
}
void LoginUi::on_tologbutton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
void LoginUi::on_tosetpage()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void LoginUi::on_registerbutton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex( 1);
}
void  LoginUi::set_loginPage()
{
    this->show();
}

void LoginUi::on_registerbutton_2_clicked()
{
    QString ip=util->getConfValue("web_server","ip");
    QString port=util->getConfValue("web_server","port");
    QString name=ui->registername->text();
    QString nickname=ui->registernickname->text();
    QString password=ui->registerpassword->text();
    QString firmpassword=ui->registerfirmpassword->text();
    QString phone=ui->registerphone->text();
    QString email=ui->registeremail->text();
    QRegularExpression qreg(USER_REG);
    if(!qreg.match(name).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户名称格式不正确");  return;
    }
    qreg.setPattern(PASSWD_REG);
    if(!qreg.match(password).hasMatch()||!qreg.match(firmpassword).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户密码格式不正确");  return;
    }
    if(password!=firmpassword)
    {
         QMessageBox::warning(this,"警告","用户两次密码不一致");  return;
    }
    qreg.setPattern(PHONE_REG);
    if(!qreg.match(phone).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户电话号码格式不正确");  return;
    }
    qreg.setPattern(EMAIL_REG);
    if(!qreg.match(email).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户电子邮件格式不正确");  return;

    }
    QNetworkRequest request;
    QString url=QString("http://%1:%2/reg").arg(ip,port);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QByteArray data;
    QJsonObject jsondata;
    jsondata.insert("userName",name);
    jsondata.insert("firstPwd",util->getStrMd5(password));
    jsondata.insert("nickName",nickname);
    jsondata.insert("phone",phone);
    jsondata.insert("email",email);
    QJsonDocument doc;
    doc.setObject(jsondata);
    data=doc.toJson();
    QNetworkReply *reply=manager->post(request,data);
    connect(reply,&QNetworkReply::readyRead,this,[=]()
            {
        QByteArray rdata=reply->readAll();
        QJsonParseError err;
        QJsonDocument rdoc=QJsonDocument::fromJson(rdata,&err);
        if(err.error!=QJsonParseError::NoError)
            {
            qDebug()<<"Json格式错误";
        }
      else
            {
            QJsonObject obj=rdoc.object();
            QJsonValue status=obj.value("code");
            if(status.type()==QJsonValue::String)
            {
                if(status.toString()=="002")
                {
                    QMessageBox::information(this,"消息","注册成功");
                }
                else if(status.toString()=="003")
                {
                    QMessageBox::information(this,"消息","注册失败，用户已存在");
                }
                else if(status.toString()=="004")
                {
                    QMessageBox::critical(this,"错误","注册失败");
                }
            }
        }
          reply->deleteLater();
    });
    }
void LoginUi::on_setserverbutton_clicked()
{
    QString address=ui->server_address->text();
    QString port=ui->server_port->text();
    QRegularExpression qreg(IP_REG);
    if(!qreg.match(address).hasMatch())
{
        QMessageBox::warning(this,"警告","IP地址格式不正确");
        return;
}
    qreg.setPattern(PORT_REG);
if(!qreg.match(port).hasMatch())
    {
         QMessageBox::warning(this,"警告","端口号格式不正确");
    return;
    }
util->writeWebserverinfo(address,port);
    ui->stackedWidget->setCurrentIndex(0);
}


void LoginUi::on_logButton_clicked()
{
    QString ip=util->getConfValue("web_server","ip");
    QString port=util->getConfValue("web_server","port");
    QString name=ui->username->text();
    QString password=ui->password->text();
    QRegularExpression qreg(USER_REG);
    if(!qreg.match(name).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户名格式不正确");
        return;
    }
    qreg.setPattern(PASSWD_REG);
    if(!qreg.match(password).hasMatch())
    {
        QMessageBox::warning(this,"警告","用户密码格式不正确");
        return;
    }
    QNetworkRequest request;
    QString url=QString("http://%1:%2/login").arg(ip,port);
      request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
      QJsonObject obj;
    obj.insert("user",name);
      obj.insert("pwd",util->getStrMd5(password));
    QJsonDocument doc;
      doc.setObject(obj);
    QByteArray data=doc.toJson();
      QNetworkReply *reply=manager->post(request,data);
    // 检查请求是否成功
    if (reply->error() == QNetworkReply::NoError) {
        connect(reply,&QNetworkReply::readyRead,this,[=](){
            QJsonParseError err;
            QByteArray rdata=reply->readAll();
             qDebug() << "服务器返回数据:" << QString(rdata);
            QJsonDocument rdoc=QJsonDocument::fromJson(rdata,&err);
            if(err.error!=QJsonParseError::NoError){
                qDebug()<<"Json格式错误";
            }
            else
            {
                QJsonObject robj=rdoc.object();
                QJsonValue status=robj.value("code");
                QJsonValue to=robj.value("token");
                if(status.type()==QJsonValue::String)
                {
                    if(status.toString()=="000")
                    {
                        QMessageBox::information(this,"消息","登录成功");
                        util->writeLogininfo(name,password,ui->rememberpwd->isChecked());
                        save_user_token(name,password,ip,port,to.toString());
                        this->hide();
                        mainui->show();
                    }
                    else if(status.toString()=="001")QMessageBox::critical(this,"错误","登录失败");
                }
            }
     reply->deleteLater();
        });
    } else {
        // 请求失败，输出错误信息
        qDebug() << "Request failed: " << reply->errorString();
        return;
    }
    }
void LoginUi::readConf()
{
    QString name=util->getConfValue("login","user");
    QString password=util->getConfValue("login","pwd");
    QString isrememeber=util->getConfValue("login","remember");
    //用户密码解密
    if(isrememeber==CFG_REMEBER_YES)
    {
        //base64解密
        QByteArray pwdTemp=QByteArray::fromBase64(password.toLocal8Bit());
        //des解密
        unsigned char encPwd[512]={0};
        int encPwdLen=0;
        int ret = DesDec((unsigned char*)pwdTemp.data(), pwdTemp.size(), encPwd, &encPwdLen);
        if(ret!=0)  {
            qDebug()<<"解密失败";
        }
        QString realpassword=QString::fromLocal8Bit((const char*)encPwd, encPwdLen);
        ui->rememberpwd->setChecked(true);
        ui->password->setText(realpassword);
    }
    else
    {
        ui->rememberpwd->setChecked(false);
        ui->password->setText("");
    }
    //用户名解密
    QByteArray userTemp = QByteArray::fromBase64(name.toLocal8Bit());
    unsigned char encUsr[512] = {0};
    int encUsrLen = 0;
    //第二步:des解密
    int ret = DesDec((unsigned char*)userTemp.data(), userTemp.size(), encUsr, &encUsrLen);
    if (ret != 0) {
        qDebug() << "解密失败";
    }
    QString userName = QString::fromLocal8Bit((const char*)encUsr, encUsrLen);
    ui->username->setText(userName);
}
void LoginUi::server_set()
{
    QString ip=util->getConfValue("web_server","ip");
    QString port=util->getConfValue("web_server","port");
    ui->server_address->setText(ip);
    ui->server_port->setText(port);
}
void LoginUi::save_user_token(QString name,QString password,QString ip,QString port,QString token)
{
    ltoken->setName(name);
    ltoken->setPassword(password);
    ltoken->setIp(ip);
    ltoken->setPort(port);
    ltoken->setToken(token);
    qDebug()<<ltoken->getToken();
}

