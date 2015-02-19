#ifndef EFFECTPLUGININTERFACE_H
#define EFFECTPLUGININTERFACE_H

#include <QObject>
#include <QtPlugin>
#include <QPixmap>
#include <QString>

class EffectPluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit EffectPluginInterface(QObject *parent = 0);
    virtual QString getPluginName() = 0;
    virtual QString getAuthorName() = 0;
    virtual float getVersion() = 0;
    virtual ~EffectPluginInterface() { }

public slots:
    virtual void execute() = 0;
    virtual void execute(QPixmap *pixmap) = 0;

signals:
    void updateImage();
    void applyChanges();
    void revertBack();

};

Q_DECLARE_INTERFACE(EffectPluginInterface, "pl.aso.qimageviewer.effectPlugin/1.0");

#endif // EFFECTPLUGININTERFACE_H
