#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>

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

    // UI events
    void resizeEvent(QResizeEvent *);
    void setMenuState(bool state);

private slots:
    void openFileDialog();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void aboutAuthorPopup();
    void aboutQtPopup();

    void updateWindowTitle(FileState state);
};

#endif // MAINWINDOW_H
