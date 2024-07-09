#ifndef MYFILEPAGE_H
#define MYFILEPAGE_H
#include "rightmenu.h"
#include <QWidget>
#include <QNetworkAccessManager>
#include "util.h"
#include "logintoken.h"
#include "file.h"
#include <QPaintEvent>
#include "filefactorui.h"
namespace Ui {
class MyFilePage;
}

class MyFilePage : public QWidget
{
    Q_OBJECT

public:
     enum MyFileDisplay { Normal, Asc, Desc};
    explicit MyFilePage(QWidget *parent = nullptr);
    ~MyFilePage();
signals:
        void loginagain();
private:
    Ui::MyFilePage *ui;
    RightMenu *iconMenu;
    FileFactorUi *filefactorui;
    Util *util;
    LoginToken *token;
    int filecount;
    RightMenu *blankMenu;
    QAction*downloadAction;
    QAction*shareAction;
    QAction*deleteAction;
    QAction*factorAction;
    QAction*ascorderAction;
    QAction*descorderAction;
    QAction*freshAction;
    QAction*uploadAction;
    QNetworkAccessManager *manager;
    QList<File*> filelist;
    void initFileList();
    void initRightMenu();
    void rightmenuconnect();
    void getUserFileCount(MyFileDisplay=Normal);
    void getUserFileList(MyFileDisplay=Normal);
    void show_FileIcon();
    void clearFile();
    //void paintEvent(QPaintEvent *event);
    void shareFile();
    void deleteFile();
    void showFileFactor();

private slots:
    void show_rightMenu(const QPoint &pos);
};

#endif // MYFILEPAGE_H
