#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *) {
    // Resize pixmap when resizeEvent on MainWindow called
    // Only when pixmap have image (not null)
    if (!pixmap.isNull())
        ui->area->setPixmap(pixmap.scaled(ui->area->width(), ui->area->height(), Qt::KeepAspectRatio));
}
