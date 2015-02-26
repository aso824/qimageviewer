#include "mainwindow.h"
#include <QApplication>

#define QT_DEBUG_PLUGINS 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
