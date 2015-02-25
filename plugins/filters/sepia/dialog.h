#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>

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
    void sliderChange(int v);
    void buttonClick(QAbstractButton *btn);
    void fullScale();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
