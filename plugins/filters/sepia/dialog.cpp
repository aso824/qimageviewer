#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChange(int)));
    connect(ui->chFull, SIGNAL(clicked()), this, SLOT(fullScale()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonClick(QAbstractButton*)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sliderChange(int v) {
    ui->edValue->setText(QString::number(v));
    emit factorChanged(v);
}

void Dialog::buttonClick(QAbstractButton *btn) {
    QDialogButtonBox::StandardButton stdbtn = ui->buttonBox->standardButton(btn);
    if (stdbtn == QDialogButtonBox::Ok)
        emit pressedOK();
    else if (stdbtn == QDialogButtonBox::Cancel)
        emit pressedCancel();
}

void Dialog::fullScale() {
    // Check checkbox state
    if (ui->chFull->isChecked()) {
        // Enable full scale
        ui->slider->setMinimum(0);
        ui->slider->setMaximum(100);
    } else {
        // Disable full scale
        ui->slider->setMinimum(20);
        ui->slider->setMaximum(40);

        // If values are out of scale, set it to min/max
        if (ui->slider->value() > 40)
            ui->slider->setValue(40);
        if (ui->slider->value() < 20)
            ui->slider->setValue(20);

        // Set value in edit box
        ui->edValue->setText(QString::number(ui->slider->value()));
    }
}
