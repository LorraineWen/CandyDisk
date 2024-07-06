#include "LoginUi.h"
#include <QApplication>
#include <QDir>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginUi l;
    l.show();
    return a.exec();
}
