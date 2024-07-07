#ifndef MAINMENUUI_H
#define MAINMENUUI_H
#include <QWidget>

namespace Ui {
class MainMenuUi;
}

class MainMenuUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuUi(QWidget *parent = nullptr);
    ~MainMenuUi();

private:
    void paintEvent(QPaintEvent *event);
    QPixmap bg;
    Ui::MainMenuUi *ui;
};

#endif // MAINMENUUI_H
