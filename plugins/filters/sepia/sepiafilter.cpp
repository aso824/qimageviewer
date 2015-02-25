#include "sepiafilter.h"

void SepiaFilter::execute(QImage *image) {
    // If QImage is null, show error and stop
    if (!image || image->isNull()) {
        QMessageBox(QMessageBox::Critical, tr("Plugin error"), tr("No image loaded."), QMessageBox::Ok).exec();
        return;
    }

    // Ptr
    img = image;

    // Make backup
    backup = QImage(*image);

    // Create form
    Dialog* dialog = new Dialog(0);

    // Make connections
    connect(dialog, SIGNAL(factorChanged(int)), this, SLOT(process(int)));
    connect(dialog, SIGNAL(pressedOK()), this, SLOT(endOK()));
    connect(dialog, SIGNAL(pressedCancel()), this, SLOT(endCancel()));

    // Show window
    dialog->show();

    // Show preview
    this->process();
}

void SepiaFilter::process(int factor) {
    // Copy from backup
    for (int i = 0; i < img->width(); i++) {
        for (int j = 0; j < img->height(); j++) {
            img->setPixel(i, j, backup.pixel(i, j));
        }
    }

    // Iterate over each pixel
    for (int i = 0; i < img->width(); i++) {
        for (int j = 0; j < img->height(); j++) {
            // Recalculate RGB for pixel
            QColor e = img->pixel(i, j);

            // Convert to greyscale
            int s = (float)e.red() * 0.299 + (float)e.green() * 0.587 + (float)e.blue() * 0.114;

            // Convert to sepia
            int r = s + 2 * factor;
            int g = s + factor;

            // Limit pixel value
            if (r > 255) r = 255;
            if (g > 255) g = 255;

            img->setPixel(i, j, QColor(r, g, e.blue()).rgb());
        }
    }

    // Emit signals
    emit updateImage();
}

void SepiaFilter::endOK() {
    emit applyChanges();
}

void SepiaFilter::endCancel() {
    qDebug() << "SepiaFilter: canceled";

    // Revert changes
    emit setImage(new QImage(backup));

    // Send signal
    emit updateImage();
}
