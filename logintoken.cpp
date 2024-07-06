#include "logintoken.h"
LoginToken*LoginToken::l_instance=new LoginToken();
LoginToken::LoginToken() {}
LoginToken* LoginToken::getInstance()
{
    return l_instance;
}
QString LoginToken::getName()
{
    return name;
}
QString LoginToken::getPassword()
{
    return password;
}
QString LoginToken::getPort()
{
    return port;
}
QString LoginToken::getIp()
{
    return ip;
}
QString LoginToken::getToken()
{
    return token;
}

void LoginToken::setName(QString name)
{
    this->name=name;
}
void LoginToken::setPassword(QString pwd)
{
    this->password=pwd;
}
void LoginToken::setPort(QString port)
{
    this->port=port;
}
void LoginToken::setIp(QString ip)
{
    this->ip=ip;
}
void LoginToken::setToken(QString token)
{
    this->token=token;
}
