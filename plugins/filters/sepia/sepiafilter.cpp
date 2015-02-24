#include "sepiafilter.h"

void SepiaFilter::execute(QImage *image) {
    this->process(image);
}

void SepiaFilter::process(QImage *image, int factor) {
    // First, convert to greyscale
    this->processGreyscale(image);

    // Iterate over each pixel
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            // Recalculate RGB for pixel
            QColor e = image->pixel(i, j);
            int r = e.red() + 2 * factor;
            int g = e.green() + factor;

            if (r > 255) r = 255;
            if (g > 255) g = 255;

            image->setPixel(i, j, QColor(r, g, e.blue()).rgb());
        }
    }

    // Emit signals
    emit updateImage();
}

void SepiaFilter::endOK() {

}

void SepiaFilter::endCancel() {

}

void SepiaFilter::processGreyscale(QImage *image) {
    // Iterate over each pixel
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            // Recalculate RGB for pixel
            QColor e = image->pixel(i, j);
            int s = (float)e.red() * 0.299 + (float)e.green() * 0.587 + (float)e.blue() * 0.114;
            image->setPixel(i, j, QColor(s, s, s).rgb());
        }
    }
}
