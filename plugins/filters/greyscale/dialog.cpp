#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Make radiobuttons connections
    connect(ui->rbAverage, SIGNAL(clicked()), this, SLOT(emitAverage()));
    connect(ui->rbYUV, SIGNAL(clicked()), this, SLOT(emitYUV()));

    // Make buttons connections
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(emitClicked(QAbstractButton*)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::emitClicked(QAbstractButton *btn) {
    QDialogButtonBox::StandardButton stdbtn = ui->buttonBox->standardButton(btn);
    if (stdbtn == QDialogButtonBox::Ok)
        emit pressedOK();
    else if (stdbtn == QDialogButtonBox::Cancel)
        emit pressedCancel();
}
