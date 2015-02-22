#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>
#include <QSettings>
#include <QActionGroup>

#include "plugininterface.h"
#include "imagemanager.h"
#include "pluginmanager.h"

enum FileState {
    NONE, OPENED, CHANGES
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ImageManager *image;
    QString fileName;
    FileState fState = NONE;
    PluginManager* plugins;
    QActionGroup *recentFilesGroup;

    // UI events
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *event);
    void loadFile(QString path);
    void setMenuState(bool state);
    QStringList loadRecent();
    void saveRecent();

private slots:
    // Menu
    void openFileDialog();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void aboutAuthorPopup();
    void aboutQtPopup();
    void recentFileSlot(QAction* action);

public slots:
    void updateWindowTitle(FileState state);
    void updateImage();
    void imageChanged();
};

#endif // MAINWINDOW_H
