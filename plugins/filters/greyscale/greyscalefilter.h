#ifndef GREYSCALEFILTER_H
#define GREYSCALEFILTER_H

#include "greyscalefilter_global.h"
#include "../../../plugininterface.h"
#include "dialog.h"

#include <QString>
#include <QMessageBox>
#include <QImage>
#include <QColor>
#include <QRgb>
#include <QDebug>

class GREYSCALEFILTERSHARED_EXPORT GreyscaleFilter : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.aso.qimageviewer.pluginInterface/1.0")
    Q_INTERFACES(PluginInterface)

    public:
        QString getPluginName() { return "Greyscale"; }
        QString getAuthorName() { return "Jan \"aso\" Szenborn"; }
        float getVersion() { return 1.0f; }
        PluginType getType() { return FILTER; }

    public slots:
        void execute(QImage *image);

    signals:
        void updateImage();
        void applyChanges();

    private slots:
        void slotAverage() { processAverage(img); }
        void slotYUV() { processYUV(img); }
        void endOK();
        void endCancel();

    protected:
        QImage *img;
        QImage backup;
        void processAverage(QImage* image);
        void processYUV(QImage* image);

};

#endif // GREYSCALEFILTER_H
