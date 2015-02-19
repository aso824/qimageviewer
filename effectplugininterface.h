#ifndef EFFECTPLUGININTERFACE_H
#define EFFECTPLUGININTERFACE_H

#include <QObject>
#include <QtPlugin>
#include <QImage>
#include <QString>

class EffectPluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~EffectPluginInterface() { }

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

Q_DECLARE_INTERFACE(EffectPluginInterface, "pl.aso.qimageviewer.effectPlugin/1.0");

#endif // EFFECTPLUGININTERFACE_H
