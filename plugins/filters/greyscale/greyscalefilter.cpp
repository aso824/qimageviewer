#include "greyscalefilter.h"

void GreyscaleFilter::execute(QImage *image) {
    // If QImage is null, show error and stop
    if (image->isNull()) {
        QMessageBox(QMessageBox::Critical, tr("Plugin error"), tr("No image loaded."), QMessageBox::Ok).exec();
        return;
    }

    // Make backup
    backup = QImage(*image);

    // Set var
    img = image;

    // Create form
    Dialog* dialog = new Dialog(0);

    // Make connections
    connect(dialog, SIGNAL(selectedAverage()), this, SLOT(slotAverage()));
    connect(dialog, SIGNAL(selectedYUV()), this, SLOT(slotYUV()));
    connect(dialog, SIGNAL(pressedOK()), this, SLOT(endOK()));
    connect(dialog, SIGNAL(pressedCancel()), this, SLOT(endCancel()));

    // Show window
    dialog->show();

    // Process default algorithm
    this->processYUV(image);
}

void GreyscaleFilter::processAverage(QImage *image) {
    qDebug() << "Generating greyscale in average algorithm";

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
}

void GreyscaleFilter::processYUV(QImage *image) {
    qDebug() << "Generating greyscale in YUV algorithm";

    // Iterate over each pixel
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            // Recalculate RGB for pixel
            QColor e = image->pixel(i, j);
            int s = (float)e.red() * 0.299 + (float)e.green() * 0.587 + (float)e.blue() * 0.114;
            image->setPixel(i, j, QColor(s, s, s).rgb());
        }
    }

    // Emit signals
    emit updateImage();
}

void GreyscaleFilter::endOK() {
    // Just send signal
    emit applyChanges();
}

void GreyscaleFilter::endCancel() {
    qDebug() << "GreyscaleFilter: canceled";

    // Revert changes
    emit setImage(new QImage(backup));

    // Send signal
    emit updateImage();
}
