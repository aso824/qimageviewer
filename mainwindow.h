#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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

    void resizeEvent(QResizeEvent *);

    // UI events
    void setMenuState(bool state);

private slots:
    void openFileDialog();
    void closeFile();
};

#endif // MAINWINDOW_H
