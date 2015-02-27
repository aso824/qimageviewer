#include "../include/imagemanager.h"

ImageManager::ImageManager(QString filename, QObject *parent) :
    QObject(parent), file(filename)
{
    // Create object
    workingCopy = new QImage();

    // If filename is given, try to load
    if (filename != "")
        load(filename);
}

bool ImageManager::load(QString filename) {
    // Reset manager
    this->reset();

    // Copy filename
    file = filename;

    // Load
    return workingCopy->load(filename);
}

void ImageManager::reset() {
    // Clear variables
    file.clear();
    current = 0;

    // Null current image
    delete workingCopy;
    workingCopy = new QImage();

    // Delete images
    foreach (QImage* img, images)
        delete img;

    // Clear vector
    images.clear();

    // Debug info
    qDebug() << "ImageManager: reset";
}

bool ImageManager::save(QString filename) {
    // When filename is not available
    if ( (filename == "") && (file == "")) {
        // Debug info
        qDebug() << "ImageManager: can't save, unknown filename";
        return false;
    }

    // Set filename
    if (filename != "")
        file = filename;

    // Debug info
    qDebug() << "ImageManager: saving to" << file;

    // Perform save
    return workingCopy->save(file);
}

void ImageManager::setCapacity(unsigned short maxCapacity) {
    // Check parameter
    if (maxCapacity < 1)
        return;

    // If it's shrink, delete images
    if (max > maxCapacity) {
        // Iterate over images and delete it
        for (unsigned int i = max; i >= maxCapacity; i++) {
            delete images.at(i);
            images.erase(images.end());
        }
    }

    // Set variable
    max = maxCapacity;
}

void ImageManager::changes() {
    // If newer images exists, delete it
    if (current > 0) {
        images.erase(images.begin(), images.begin() + current);
        current = 0;
    }

    // Copy working image to history
    images.push_front(new QImage(*workingCopy));

    // Delete old images
    if (images.size() > max) {

        images.erase(images.begin() + max, images.end());
    }
}

void ImageManager::undo() {
    // No older copies
    if (current >= images.size() - 1) {
        // Debug info
        qDebug() << "ImageManager: no older copies to undo!";
        return;
    }

    // Set current image to previous
    workingCopy = images.at(current + 1);

    // Increase index
    current++;

    // Emit signals
    emit redraw();

    // Debug info
    qDebug() << "ImageManager: undo";
}

void ImageManager::redo() {
    if (current < 1) {
        // Debug info
        qDebug() << "ImageManager: no newer copies to redo!";
        return;
    }

    // Set current image to next
    workingCopy = images.at(current + 1);

    // Decrease index
    current--;

    // Emit signals
    emit redraw();

    // Debug info
    qDebug() << "ImageManager: redo";
}
