#ifndef TITLEUI_H
#define TITLEUI_H

#include <QWidget>

namespace Ui {
class TitleUi;
}

class TitleUi : public QWidget
{
    Q_OBJECT

public:
    explicit TitleUi(QWidget *parent = nullptr);
    ~TitleUi();
signals:
    void show_setpage();
    void show_logpage();
    void show_registerpage();
private slots:
    void on_tosetbutton_clicked();

    void on_tologbutton_clicked();

    void on_toregisterbutton_clicked();

private:
    Ui::TitleUi *ui;
};

#endif // TITLEUI_H
