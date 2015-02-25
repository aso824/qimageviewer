#include "manageplugins.h"
#include "ui_manageplugins.h"

ManagePlugins::ManagePlugins(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagePlugins)
{
    ui->setupUi(this);

    // Radiobuttons
    connect(ui->rbLoadAll, SIGNAL(clicked()), this, SLOT(rbAllClicked()));
    connect(ui->rbLoadSelected, SIGNAL(clicked()), this, SLOT(rbSelectedClicked()));
}

ManagePlugins::~ManagePlugins()
{
    delete ui;
}

void ManagePlugins::rbAllClicked() {
    ui->tabWidget->setDisabled(true);
}

void ManagePlugins::rbSelectedClicked() {
    ui->tabWidget->setEnabled(true);
}
