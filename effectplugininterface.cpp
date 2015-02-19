#include "effectplugininterface.h"

EffectPluginInterface::EffectPluginInterface(QObject *parent) :
    QObject(parent)
{
}

void EffectPluginInterface::setImage(QImage *newImage) {
    image = newImage;
}
