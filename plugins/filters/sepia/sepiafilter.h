#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H

#include "sepiafilter_global.h"
#include "../../../plugininterface.h"

#include <QImage>
#include <QColor>

class SEPIAFILTERSHARED_EXPORT SepiaFilter : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.aso.qimageviewer.pluginInterface/1.0")
    Q_INTERFACES(PluginInterface)

    public:
        QString getPluginName() { return "Sepia"; }
        QString getAuthorName() { return "Jan \"aso\" Szenborn"; }
        float getVersion() { return 1.0f; }
        PluginType getType() { return FILTER; }

    public slots:
        void execute(QImage *image);

    signals:
        void updateImage();
        void applyChanges();

    private slots:
        void process(QImage *image, int factor = 30);
        void endOK();
        void endCancel();

    protected:
        QImage *img;
        QImage backup;
        void processGreyscale(QImage *image);
};

#endif // SEPIAFILTER_H
