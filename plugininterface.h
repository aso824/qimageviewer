#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QtPlugin>
#include <QImage>
#include <QString>

enum PluginType { TOOL, FILTER };

class PluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~PluginInterface() { }

    virtual QString getPluginName() = 0;
    virtual QString getAuthorName() = 0;
    virtual float getVersion() = 0;
    virtual PluginType getType() = 0;

public slots:
    virtual void execute(QImage *image) = 0;

signals:
    void updateImage();
    void applyChanges();
    void revertBack();
    void finished();

};

Q_DECLARE_INTERFACE(PluginInterface, "pl.aso.qimageviewer.pluginInterface/1.0");

#endif // PLUGININTERFACE_H
