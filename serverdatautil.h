#ifndef SERVERDATAUTIL_H
#define SERVERDATAUTIL_H
#include<QObject>
#include<QByteArray>
#include "file.h"
class ServerDataUtil:public QObject
{
    Q_OBJECT
public:
    ServerDataUtil();
    static QStringList getFileCount(QByteArray json);
    static QList<File*>getFileInfo(QByteArray json);
    static QString getCode(QByteArray json);
};

#endif // SERVERDATAUTIL_H
