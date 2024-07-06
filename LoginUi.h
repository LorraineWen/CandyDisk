#ifndef LOGINUI_H
#define LOGINUI_H
#include <QWidget>
#include<QPainter>
#include "util.h"
#include"logintoken.h"
namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);
    explicit LoginUi(QWidget *parent = nullptr);
    void readConf();
     void server_set();
    void save_user_token(QString name,QString password,QString ip,QString port,QString token);
    ~LoginUi();

private slots:
    //界面转换槽函数
    void on_tologbutton_2_clicked();
    void on_tosetpage();
    void on_registerbutton_4_clicked();
    //业务功能槽函数
    void on_registerbutton_2_clicked();
    void on_setserverbutton_clicked();
    void on_logButton_clicked();

private:
    Ui::LoginUi *ui;
    Util *util;
    LoginToken *ltoken;
};

#endif // LOGINUI_H