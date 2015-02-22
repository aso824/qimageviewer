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
    void selectedAverage();
    void selectedYUV();
    void pressedOK();
    void pressedCancel();

private slots:
    void emitAverage() { emit selectedAverage(); }
    void emitYUV() { emit selectedYUV(); }
    void emitClicked(QAbstractButton *btn);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
