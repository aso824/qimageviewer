#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>
#include <QPluginLoader>
#include <QVector>
#include <QPair>

#include "effectplugininterface.h"

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
    QPixmap pixmap;
    QString fileName;
    FileState fState = NONE;
    QVector<QPair<EffectPluginInterface*, QPluginLoader*>> effects;

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
    void loadEffects();

public slots:
    void updateWindowTitle(FileState state);
};

#endif // MAINWINDOW_H
