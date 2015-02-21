#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QVector>
#include <QImage>
#include <QString>
#include <QDebug>

class ImageManager : public QObject
{
    Q_OBJECT

    public:
        explicit ImageManager(QString filename = "", QObject *parent = 0);
        ImageManager(QString filename);

        // Basic manager functions
        bool load(QString filename);
        void reset();
        bool save(QString filename = "");
        inline QImage* get() { return workingCopy; }

        // Capacity & index functions
        void setCapacity(unsigned short maxCapacity);
        unsigned short inline getCapacity() { return max; }
        unsigned short inline getCurrentIndex() { return current; }

        // Getters
        inline int width() { return workingCopy->width(); }
        inline int height() { return workingCopy->height(); }

    signals:
        // Manager emit this when current image changed
        void redraw();

    public slots:
        // Inform manager that any changes was made
        void changes();

        // Undo and redo changes
        void undo();
        void redo();

    protected:
        // Memory for current and past images
        QImage* workingCopy;
        QVector<QImage*> images;

        // Actual filename
        QString file;

        // Maximum number of stored images
        unsigned short max = 5;

        // Current image index (newest is 0)
        unsigned short current = 0;
};

#endif // IMAGEMANAGER_H
