#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>
#include <QPluginLoader>
#include <QVector>
#include <QPair>

#include "filterplugininterface.h"

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
    QImage *image;
    QString fileName;
    FileState fState = NONE;
    QVector<QPair<FilterPluginInterface*, QPluginLoader*>> filters;

    // UI events
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *event);
    void setMenuState(bool state);

private slots:
    // Menu
    void openFileDialog();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void aboutAuthorPopup();
    void aboutQtPopup();

    // Plugins
    void loadTools();
    void loadFilters();

public slots:
    void updateWindowTitle(FileState state);
    void updateImage();
};

#endif // MAINWINDOW_H
