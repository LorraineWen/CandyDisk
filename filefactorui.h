#ifndef FILEFACTORUI_H
#define FILEFACTORUI_H

#include <QWidget>
#include "file.h"
#include <QDialog>
#include<QPaintEvent>
namespace Ui {
class FileFactorUi;
}

class FileFactorUi : public QWidget
{
    Q_OBJECT

public:
    explicit FileFactorUi(QWidget *parent = nullptr);
    ~FileFactorUi();
    void setFileFactor(File*file);
    void paintEvent(QPaintEvent*event);
private:
    Ui::FileFactorUi *ui;
    QPixmap bg;

};
#endif // FILEFACTORUI_H
