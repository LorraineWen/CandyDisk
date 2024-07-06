#ifndef LOGINTOKEN_H
#define LOGINTOKEN_H
#include<QString>
class LoginToken
{
public:
  static  LoginToken*getInstance();
    QString getName();
    QString getPassword();
    QString getPort();
    QString getIp();
    QString getToken();
   void setName(QString name);
   void setPassword(QString pwd);
  void setPort(QString port);
   void setIp(QString ip);
   void setToken(QString token);
private:
    static LoginToken*l_instance;
     LoginToken();
    QString name;
    QString password;
    QString port;
    QString ip;
    QString token;
};

#endif // LOGINTOKEN_H
