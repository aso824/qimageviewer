#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect menu elements
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
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
    QString fileNameTmp = QFileDialog::getOpenFileName(this, tr("Open image"), "",
                          tr("Supported image types (*.jpg *.jpeg *.png *.gif *.bmp);;JPEG (*.jpg *.jpeg);;PNG (*.png);;GIF(*.gif);;Windows bitmap (*.bmp)"));

    if (fileNameTmp != "")
        fileName = fileNameTmp;
    else
        return;

    // Try to load
    if (pixmap.load(fileName)) {
        // Fill QLabel with pixmap
        ui->area->setPixmap(pixmap);

        // Enable menus
        setMenuState(true);

        // Change window title
        updateWindowTitle(OPENED);
    } else {
        // Show error
        QMessageBox(QMessageBox::Critical, tr("Error"), tr(QString("Can't open file \"" + fileName + "\"!").toStdString().c_str()), QMessageBox::Ok, this)
                .exec();
    }
}

void MainWindow::saveFile() {
    // Check pixmap
    if (!pixmap.isNull()) {
        // Perform save
        pixmap.save(fileName);
    }
}

void MainWindow::saveFileAs() {
    // Chec pixmap
    if (!pixmap.isNull()) {
        // Ask for file name
        QString fileNameTmp = QFileDialog::getSaveFileName(this, tr("Save image as"), "",
                              tr("JPEG (*.jpg);;PNG (*.png);;GIF (*.gif);;Windows bitmap (*.bmp)"));

        if (fileNameTmp != "")
            fileName = fileNameTmp;
        else
            return;

        // Perform save
        pixmap.save(fileName);

        // Change window title
        updateWindowTitle(OPENED);
    }
}

void MainWindow::closeFile() {
    // Hide image
    ui->area->clear();

    // Clear file name
    fileName.clear();

    // Disable menus
    setMenuState(false);

    // Restore window title
    updateWindowTitle(NONE);
}

void MainWindow::setMenuState(bool state) {
    ui->actionClose->setEnabled(state);
    ui->actionSave->setEnabled(state);
    ui->actionSave_as->setEnabled(state);
    ui->menuEdit->setEnabled(state);
    ui->menuEffects->setEnabled(state);
    ui->menuTools->setEnabled(state);
}

void MainWindow::updateWindowTitle(FileState state) {
    // Set global file state to given state
    fState = state;

    // Basic variables
    const QString appName = "QImageViewer";
    QString newTitle;

    // This variable holds only file name, not full path
    QString fName = QFileInfo(fileName).fileName();

    // Construct window title
    switch (state) {
        case NONE:      newTitle = appName; break;
        case OPENED:    newTitle = fName + " - " + appName; break;
        case CHANGES:   newTitle = "[*]" + fName + " - " + appName; break;
        default:        newTitle = appName;
    }

    // Set it
    this->setWindowTitle(newTitle);
}
