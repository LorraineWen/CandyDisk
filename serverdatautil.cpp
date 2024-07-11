#include "serverdatautil.h"
#include<QJsonParseError>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
ServerDataUtil::ServerDataUtil()
{}
QStringList ServerDataUtil::getFileCount(QByteArray json)
{
    QStringList list;
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(json,&err);
    if(err.error!=QJsonParseError::NoError)
    {
        qDebug()<<"getFileCount的Json格式错误";
    }
    else
    {
        QJsonObject obj=doc.object();
        QJsonValue code=obj.value("code");
        QJsonValue num=obj.value("num");
        if(code.type()==QJsonValue::String)
        {
            list.append(code.toString());
        }
        if(num.type()==QJsonValue::String)
        {
            list.append(num.toString());

        }
    }
    return list;
}
QList<File*>ServerDataUtil::getFileInfo(QByteArray json)
{
    QList<File*> list;
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(json,&err);
    if(err.error!=QJsonParseError::NoError)
    {
        qDebug()<<"getFileInfo的json格式错误";
    }
    else
    {
        QJsonObject obj=doc.object();
        QJsonValue v=obj.value("files");
        if(v.type()==QJsonValue::Array)
        {
            QJsonArray arr=v.toArray();
            for(int i=0;i<arr.size();i++)
            {
                QJsonValue filevalue=arr.at(i);
                if(filevalue.type()==QJsonValue::Object)
                {
                    QJsonObject obj2=filevalue.toObject();
                     File*file=new File();
                    QJsonValue uservalue=obj2.value("user");
                     QJsonValue md5value=obj2.value("md5");
                    QJsonValue createtimevalue=obj2.value("create_time");
                    QJsonValue filenamevalue=obj2.value("file_name");
                    QJsonValue sharestatusvalue=obj2.value("share_status");
                     QJsonValue pvvalue=obj2.value("pvr");
                    QJsonValue urlvalue=obj2.value("url");
                     QJsonValue sizevalue=obj2.value("size");
                    QJsonValue typevalue=obj2.value("type");
                    file->user = uservalue.toString();
                    file->md5 = md5value.toString();
                    file->createTime = createtimevalue.toString();
                    file->fileName = filenamevalue.toString();
                    file->shareStatus = sharestatusvalue.toInt();
                    file->pv = pvvalue.toInt();
                    file->url = urlvalue.toString();
                    file->size = sizevalue.toInt();
                    file->type = typevalue.toString();
                    list.append(file);
                }

            }
        }
    }
    return list;
}
QString ServerDataUtil::getCode(QByteArray json)
{
    QString code;
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(json,&err);
    if(err.error!=QJsonParseError::NoError)
    {
        qDebug()<<"getCode的Json格式错误";
    }else
    {
        QJsonObject obj=doc.object();
        QJsonValue value=obj.value("code");
        if(value.type()==QJsonValue::String)
        {
            code=value.toString();
        }
    }
    return code;
}
