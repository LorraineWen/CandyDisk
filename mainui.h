#ifndef MAINUI_H
#define MAINUI_H
#include "mainmenuui.h"
#include <QWidget>
namespace Ui {
class MainUi;
}

class MainUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainUi(QWidget *parent = nullptr);
    ~MainUi();
signals:void show_loginPage();

private slots:

private:
    Ui::MainUi *ui;
    void mainconnect();
};

#endif // MAINUI_H
