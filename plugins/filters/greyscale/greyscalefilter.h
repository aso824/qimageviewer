#ifndef GREYSCALEFILTER_H
#define GREYSCALEFILTER_H

#include "greyscalefilter_global.h"
#include "../../filterplugininterface.h"

#include <QString>
#include <QMessageBox>

class GREYSCALEFILTERSHARED_EXPORT GreyscaleFilter : public FilterPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.aso.qimageviewer.filterPlugin/1.0")
    Q_INTERFACES(FilterPluginInterface)

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

#endif // GREYSCALEFILTER_H
