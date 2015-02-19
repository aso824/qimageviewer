#include "greyscalefilter.h"

void GreyscaleFilter::execute() {
    // If QImage is null, show error and stop
    if (image->isNull()) {
        QMessageBox(QMessageBox::Critical, tr("Plugin error"), tr("No image loaded."), QMessageBox::Ok).exec();
        return;
    }

    // Iterate over each pixel
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            // Recalculate RGB for pixel
            QColor e = image->pixel(i, j);
            int s = ( e.red() + e.green() + e.blue() ) / 3;
            image->setPixel(i, j, QColor(s, s, s).rgb());
        }
    }

    // Emit signals
    emit updateImage();
    emit applyChanges();
    emit finished();
}
