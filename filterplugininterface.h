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

public slots:
    virtual void execute(QImage *image) = 0;

signals:
    void updateImage();
    void applyChanges();
    void revertBack();
    void finished();

};

Q_DECLARE_INTERFACE(FilterPluginInterface, "pl.aso.qimageviewer.filterPlugin/1.0");

#endif // FILTERPLUGININTERFACE_H
