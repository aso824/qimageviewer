#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:
    void pressedOK();
    void pressedCancel();
    void factorChanged(int);

private slots:
    void sliderChange(int v) { emit factorChanged(v); }
    void buttonOK() { emit pressedOK(); }
    void buttonCancel() { emit pressedCancel(); }

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
