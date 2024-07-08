#include "util.h"
#include<QCryptographicHash>
#include"des.h"
#include<QDebug>
#include<QMap>
#include<QVariant>
#include<QJsonDocument>
#include <QFile>
#include<QJsonObject>
Util* Util::u_instance=new Util;
Util::Util()
{
    manger=new QNetworkAccessManager();
}
Util* Util::get_instance()
{
    return u_instance;
}
void Util::writeWebserverinfo(QString ip,QString port,QString path)
{
    QString name=getConfValue("login","user");
    QString pwd=getConfValue("login","pwd");
    QString isremember=getConfValue("login","remember");
    QMap<QString,QVariant>login;
    login.insert("user",name);
    login.insert("pwd",pwd);
    login.insert("remember",isremember);
    QMap<QString,QVariant>web_server;
    web_server.insert("ip",ip);
    web_server.insert("port",port);
    QMap<QString,QVariant>json;
    json.insert("login",login);
    json.insert("web_server",web_server);
    QJsonDocument doc=QJsonDocument::fromVariant(json);
    if(doc.isNull())
    {
        qDebug()<<"QJsonDocument::fromVariant错误";
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"cfg.json文件打开失败";
    }
    else
    {
        file.write(doc.toJson());
    }
    if(file.isOpen())file.close();
}
void Util::writeLogininfo(QString user,QString pwd,bool isRemember,QString path)
{
    //服务器设置写入配置文件
    QString ip=getConfValue("web_server","ip");
    QString port=getConfValue("web_server","port");
    QMap<QString,QVariant>webserver;
    webserver.insert("ip",ip);
    webserver.insert("port",port);
    //登录加密
    //des加密
    //用户名称加密
    unsigned char encUser[1024]={0};
    int encUsrLen;
    int ret=DesEnc((unsigned char*)user.toLocal8Bit().data(),user.toLocal8Bit().length(),encUser,&encUsrLen);
    if(ret!=0)
    {
        //加密失败
        qDebug()<<"Des加密用户名称失败";
        return;
    }
    //用户密码加密
    unsigned char encPwd[1024]={0};
    int encPwdLen;
    ret=DesEnc((unsigned char *)pwd.toLocal8Bit().data(),pwd.toLocal8Bit().length(),encPwd,&encPwdLen);
    if(ret!=0)
    {
        //加密失败
        qDebug()<<"Des加密用户密码失败";
        return;
    }
    //base64加密
    QString base64User=QByteArray((char*)encUser,encUsrLen).toBase64();
    QString base64Pwd=QByteArray((char*)encPwd,encPwdLen).toBase64();

    //将数据封装为json格式
    QMap<QString,QVariant>login;//要入两个头文件
    login.insert("pwd",base64Pwd);
    login.insert("user",base64User);
    if(isRemember)
    {
        login.insert("remember",CFG_REMEBER_YES);
    }
    else
    {
        login.insert("remember",CFG_REMEBER_NO);
    }
    QMap<QString,QVariant>json;
    json.insert("login",login);
    json.insert("web_server",webserver);
    QJsonDocument doc=QJsonDocument::fromVariant(json);
    if(doc.isNull())
    {
        qDebug()<<"QJsonDocument::fromVariant错误";
        return;
    }

    //将json保存到配置文件中
    QFile file(path);
    if(false==file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"文件打开失败";

    }
    else
    {
        file.write(doc.toJson());
    }
    if(file.isOpen())file.close();
}
QString Util::getStrMd5(QString str)
{
    QByteArray arr;
    arr=QCryptographicHash::hash(str.toLocal8Bit(),QCryptographicHash::Md5);
    return arr.toHex();
}
QNetworkAccessManager* Util::getmanger()
{
    return manger;
}

QString Util::getConfValue(QString title,QString key,QString path)
{
    QFile file(path);
    if(false==file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开cfg.json文件失败";
        return "";
    }
    QByteArray json=file.readAll();//将cfg.json中的所有文件都读取出来
    if(file.isOpen())
    {
        file.close();
    }
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(json,&err);
    if(err.error!=QJsonParseError::NoError)
    {
        qDebug()<<"json格式错误";
    }
    else
    {
        if(doc.isNull()||doc.isEmpty())
        {
            qDebug()<<"doc为NULL或者为空";
        }
        else if(doc.isObject())
        {
            QJsonObject obj=doc.object();
            QJsonValue titleValue=obj.value(title);
            if(titleValue.type()==QJsonValue::Object)
            {
                QJsonObject titleObj=titleValue.toObject();
                QStringList list=titleObj.keys();
                for(int i=0;i<list.size();i++)
                {
                    QString keyTemp=list.at(i);
                    if(keyTemp==key)
                    {
                        return titleObj.value(key).toString();
                    }
                }
            }
        }
    }
    return "";
}
