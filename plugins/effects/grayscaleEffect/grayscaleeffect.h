#ifndef GRAYSCALEEFFECT_H
#define GRAYSCALEEFFECT_H

#include "grayscaleeffect_global.h"
#include "../../effectplugininterface.h"

#include <QString>
#include <QMessageBox>

class GRAYSCALEEFFECTSHARED_EXPORT GrayscaleEffect : public EffectPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.aso.qimageviewer.effectPlugin/1.0")
    Q_INTERFACES(EffectPluginInterface)

    public:
        QString getPluginName() { return "Greyscale"; }
        QString getAuthorName() { return "Jan \"aso\" Szenborn"; }
        float getVersion() { return 1.0f; }

    public slots:
        void execute();

    signals:
        void updateImage();
        void applyChanges();
        void revertBack();

};

#endif // GRAYSCALEEFFECT_H
