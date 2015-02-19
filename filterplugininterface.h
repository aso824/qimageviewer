#ifndef FILTERPLUGININTERFACE_H
#define FILTERPLUGININTERFACE_H

#include <QObject>
#include <QtPlugin>
#include <QImage>
#include <QString>

class FilterPluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~FilterPluginInterface() { }

    virtual QString getPluginName() = 0;
    virtual QString getAuthorName() = 0;
    virtual float getVersion() = 0;
    void setImage(QImage *newImage);

public slots:
    virtual void execute() = 0;

signals:
    void updateImage();
    void applyChanges();
    void revertBack();

protected:
    QImage *image;

};

Q_DECLARE_INTERFACE(FilterPluginInterface, "pl.aso.qimageviewer.filterPlugin/1.0");

#endif // FILTERPLUGININTERFACE_H
