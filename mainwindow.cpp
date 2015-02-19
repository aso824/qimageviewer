#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create QImage
    image = new QImage();

    // Allow QLabel with QPixmap to scale down
    ui->area->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    // Connect menu elements
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui->actionAbout_author, SIGNAL(triggered()), this, SLOT(aboutAuthorPopup()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQtPopup()));

    // Load plugins
    loadTools();
    loadEffects();
}

MainWindow::~MainWindow()
{
    // Free plugins
    unsigned int effectsCount = 0;
    QPair<EffectPluginInterface*, QPluginLoader*> pair1;
    foreach (pair1, effects) {
        pair1.second->unload();
        //delete pair1.first;
        //delete pair1.second;
        effectsCount++;
    }

    qDebug() << "Unloaded" << effectsCount << "effects";

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *) {
    // If centralWidget size is smaller than pixmap, scale image
    if (
            (ui->centralWidget->width() < image->width()) ||
            (ui->centralWidget->height() < image->height())
        ) {

        // Just set pixmap scaled with ratio to w/h of centralWidget
        ui->area->setPixmap(
                    QPixmap::fromImage(*image).scaled(
                        ui->centralWidget->width(),
                        ui->centralWidget->height(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation));
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Check if actually opened file is modified
    if (fState == CHANGES) {
        // Ask about save
        QMessageBox::StandardButton reply =
                QMessageBox::question(this, tr("Unsaved changes"),
                                      tr(QString("You have unsaved changes in file " + fileName + "<br>"
                                                 "Do you want do save file?").toStdString().c_str()),
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            // When hit "Yes", save file and exit
            this->saveFile();
        } else if (reply == QMessageBox::Cancel) {
            // When hit "cancel" don't close
            event->ignore();
        } else {
            // "No" button hit, which mean no save and exit
            event->accept();
        }
    }
}

void MainWindow::openFileDialog() {
    // Ask for file to open
    QString fileNameTmp = QFileDialog::getOpenFileName(this, tr("Open image"), "",
                          tr("Supported image types (*.jpg *.jpeg *.png *.gif *.bmp);;JPEG (*.jpg *.jpeg);;PNG (*.png);;GIF(*.gif);;Windows bitmap (*.bmp)"));

    qDebug() << "QFileDialog returned" << fileNameTmp;

    if (fileNameTmp != "")
        fileName = fileNameTmp;
    else
        return;

    // Try to load
    if (image->load(fileName)) {
        // Fill QLabel with pixmap
        ui->area->setPixmap(QPixmap::fromImage(*image));

        // Call resizeEvent to scale image
        QResizeEvent *resizeEvent = new QResizeEvent(this->size(), this->size());
        this->resizeEvent(resizeEvent);

        // Enable menus
        setMenuState(true);

        // Change window title
        updateWindowTitle(OPENED);

        // Debug info
        qDebug() << "Opened file" << fileName;
    } else {
        // Show error
        QMessageBox(QMessageBox::Critical, tr("Error"), tr(QString("Can't open file \"" + fileName + "\"!").toStdString().c_str()), QMessageBox::Ok, this)
                .exec();
    }
}

void MainWindow::saveFile() {
    // Check pixmap
    if (!image->isNull()) {
        // Perform save
        image->save(fileName);

        // Debug info
        qDebug() << "Saved file to" << fileName;
    } else {
        // Debug info
        qDebug() << "Can't save file - pixmap is null!";
    }
}

void MainWindow::saveFileAs() {
    // Chec pixmap
    if (!image->isNull()) {
        // Ask for file name
        QString fileNameTmp = QFileDialog::getSaveFileName(this, tr("Save image as"), "",
                              tr("JPEG (*.jpg);;PNG (*.png);;GIF (*.gif);;Windows bitmap (*.bmp)"));

        qDebug() << "Filename to save:" << fileNameTmp;

        // If user hit cancel, QFileDialog will return empty string
        if (fileNameTmp == "")
            return;

        // Perform save
        if (image->save(fileNameTmp)) {
            // Update variable
            fileName = fileNameTmp;

            // Change window title
            updateWindowTitle(OPENED);

            // Debug info
            qDebug() << "\"Save As\" to" << fileName;
        } else {
            // Display info
            QMessageBox(QMessageBox::Critical, tr("Error"),
                        tr(QString("Cannot save file " + fileNameTmp).toStdString().c_str()),
                        QMessageBox::Ok, this).exec();
            // Debug info
            qDebug() << "Error while saving as" << fileNameTmp;
        }
    }
}

void MainWindow::closeFile() {
    // If file is modified, ask user what to do
    if (fState == CHANGES) {
        // Ask about save
        QMessageBox::StandardButton reply =
                QMessageBox::question(this, tr("Unsaved changes"),
                                      tr(QString("You have unsaved changes in file " + fileName + "<br>"
                                                 "Do you want do save file?").toStdString().c_str()),
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            // When hit "Yes", save file and continue function
            this->saveFile();
        } else if (reply == QMessageBox::Cancel) {
            // When hit "cancel" exit function
            return;
        } else {
            // "No" button hit, which mean no save and close
            // No actions here.
        }
    }


    // Debug info
    qDebug() << "Closing file" << fileName;

    // Hide image
    ui->area->clear();

    // Clear file name
    fileName.clear();

    // Restore empty window title
    updateWindowTitle(NONE);

    // Disable menus
    setMenuState(false);
}

void MainWindow::aboutAuthorPopup() {
    QString text = "Author: Jan \"aso\" Szenborn<br>"
                   "<a href=\"http://aso.uh.net.pl\">aso.uh.net.pl</a><br>"
                   "<a href=\"http://github.com/aso824/qimageviewer\">github.com/aso824/qimageviewer</a><br><br>"
                   "This program is on LGPL license. See LICENSE.txt for details.";
    QMessageBox::about(this, tr("About author"), tr(text.toStdString().c_str()));
}

void MainWindow::aboutQtPopup() {
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::setMenuState(bool state) {
    // Set enabled or disabled on specific elements
    ui->actionClose->setEnabled(state);
    ui->actionSave->setEnabled(state);
    ui->actionSave_as->setEnabled(state);
    ui->menuEdit->setEnabled(state);
    ui->menuEffects->setEnabled(state);
    ui->menuTools->setEnabled(state);

    // Debug info
    qDebug() << "Set menu state to" << state;
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
        case CHANGES:   newTitle = "(*) " + fName + " - " + appName; break;
        default:        newTitle = appName;
    }

    // Set it
    this->setWindowTitle(newTitle);

    // Debug info
    qDebug() << "Updating window title with state =" << state;
}

void MainWindow::loadTools() {
    //
}

void MainWindow::loadEffects() {
    // Set plugin directory
    QDir pluginsDir("plugins/effects");
    qDebug() << "Loading effects from" << pluginsDir.absolutePath();

    // File filter
    QStringList filters;
    #ifdef __linux
        filters << "*.so";
    #elif _WIN32
        filters << "*.dll";
    #endif

    // Iterate over files
    unsigned int pluginCount = 0;
    foreach (QString filename, pluginsDir.entryList(filters)) {
        // Ignore files without "effect" in name
        if (!filename.toLower().contains("effect"))
            continue;

        // Try to load
        QPluginLoader *loader = new QPluginLoader(pluginsDir.absoluteFilePath(filename));
        QObject *pluginInstance = loader->instance();

        if (pluginInstance) {
            // Cast QObject to plugin
            EffectPluginInterface *plugin = qobject_cast<EffectPluginInterface*>(pluginInstance);

            // Check if loaded correct
            if (plugin) {

                // Give plugin an image
                plugin->setImage(image);

                // Add plugin to vector
                effects.push_back(QPair<EffectPluginInterface*, QPluginLoader*>(plugin, loader));

                // If this is first plugin, clear list
                if (pluginCount == 0)
                    ui->menuEffects->clear();

                // Add menu entry
                QAction *menuAction = ui->menuEffects->addAction(tr(plugin->getPluginName().toStdString().c_str()));
                connect(menuAction, SIGNAL(triggered()), plugin, SLOT(execute()));

                // Increase counter
                pluginCount++;
            } else {
                qDebug() << "Failed to load effect" << filename;
            }
        } else {
            qDebug() << "Can't' load effect plugin from file" << filename;
            qDebug() << "Error:" << loader->errorString();
        }
    }

    // Debug info
    qDebug() << "Loaded" << pluginCount << "effects.";

}