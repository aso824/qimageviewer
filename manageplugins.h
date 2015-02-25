#ifndef MANAGEPLUGINS_H
#define MANAGEPLUGINS_H

#include <QDialog>

namespace Ui {
class ManagePlugins;
}

class ManagePlugins : public QDialog
{
    Q_OBJECT

public:
    explicit ManagePlugins(QWidget *parent = 0);
    ~ManagePlugins();

private slots:
    void rbAllClicked();
    void rbSelectedClicked();

private:
    Ui::ManagePlugins *ui;
};

#endif // MANAGEPLUGINS_H
