#ifndef UTIL_H
#define UTIL_H
#include<QString>
#include <QObject>
#include<QNetworkAccessManager>
// 正则表达式
#define USER_REG        "^[a-zA-Z\\d_@#-\*]\{3,16\}$"
#define PASSWD_REG      "^[a-zA-Z\\d_@#-\*]\{6,18\}$"
#define PHONE_REG       "1\\d\{10\}"
#define EMAIL_REG       "^[a-zA-Z\\d\._-]\+@[a-zA-Z\\d_\.-]\+(\.[a-zA-Z0-9_-]\+)+$"
#define IP_REG          "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)"
#define PORT_REG        "^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)"
//配置文件
#define CFG_FILE "conf/cfg.json"
#define CFG_REMEBER_YES "yes"
#define CFG_REMEBER_NO "no"
#define FILE_TYPE_DIR "conf/filetype"
class Util
{

private: Util();
    static Util* u_instance;
    QNetworkAccessManager *manger;
public:
    static Util* get_instance();
    //写入数据到文件
    void writeLogininfo(QString user,QString pwd,bool isRemeber,QString path=CFG_FILE);
    void writeWebserverinfo(QString ip,QString port,QString path=CFG_FILE);
    //读取文件数据
    QString getConfValue(QString title,QString key,QString path=CFG_FILE);
    //加密字符串
    QString getStrMd5(QString str);
    QNetworkAccessManager* getmanger();
    QString getFileType(QString filetypename);
    void getFileTypeList();
private:
    QStringList filetypelist;
};

#endif // UTIL_H
