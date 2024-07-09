#ifndef MAINMENUUI_H
#define MAINMENUUI_H
#include <QWidget>
#include <QSignalMapper>
#include <QToolButton>
#include "logintoken.h"
namespace Ui {
class MainMenuUi;
}

class MainMenuUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuUi(QWidget *parent = nullptr);
    ~MainMenuUi();
signals:
    void show_myfilePage();
    void show_sharefilePage();
    void show_downloadfilePage();
    void show_transportfilePage();
    void show_changeuserPage();
private slots:
    //void onMapperButtonClicked(QString);
    void menuconnect();
private:
    void paintEvent(QPaintEvent *event);
   //void defaultPage();
    QPixmap bg;
    Ui::MainMenuUi *ui;
    LoginToken *token;
    //QSignalMapper* smapper;
    //QMap<QString,QToolButton*>mapper;
    //QToolButton*currentButton;
};

#endif // MAINMENUUI_H
