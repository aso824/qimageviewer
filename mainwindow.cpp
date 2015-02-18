#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect menu elements
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *) {
    // Resize pixmap when resizeEvent on MainWindow called
    // Only when pixmap have image (not null)
    if (!pixmap.isNull()) {
        int w = (ui->area->width() < pixmap.width()) ? ui->area->width() : pixmap.width();
        int h = (ui->area->height() < pixmap.height()) ? ui->area->height() : pixmap.height();
        ui->area->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::openFileDialog() {
    // Ask for file to open
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), "",
            tr("Supported image types (*.jpg *.jpeg *.png *.gif *.bmp);;JPEG (*.jpg *.jpeg);;PNG (*.png);;GIF(*.gif);;Windows bitmap (*.bmp)"));

    // Try to load
    if (pixmap.load(fileName)) {
        // Fill QLabel with pixmap
        ui->area->setPixmap(pixmap);

        // Enable menus
        setMenuState(true);
    } else {
        // Show error
        QMessageBox(QMessageBox::Critical, tr("Error"), tr(QString("Can't open file \"" + fileName + "\"!").toStdString().c_str()), QMessageBox::Ok, this)
                .exec();
    }
}

void MainWindow::closeFile() {
    // Hide image
    ui->area->clear();

    // Disable menus
    setMenuState(false);
}

void MainWindow::setMenuState(bool state) {
    ui->actionClose->setEnabled(state);
    ui->actionSave->setEnabled(state);
    ui->menuEdit->setEnabled(state);
    ui->menuEffects->setEnabled(state);
    ui->menuTools->setEnabled(state);
}
