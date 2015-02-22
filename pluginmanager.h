#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QVariant>
#include <QMap>
#include <QPair>
#include <QPluginLoader>
#include <QString>
#include <QDebug>
#include <QMenu>
#include <QStringList>
#include <QDir>
#include <QDirIterator>

#include "plugininterface.h"
#include "imagemanager.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    // Plugins management functions
    void loadAll();
    bool load(QString filename);

    void unloadAll();
    bool unload(QString filename);

    QStringList getToolsFilenames();
    QStringList getFiltersFilenames();
    QStringList getPluginsFilenames();

    // Getters
    PluginInterface* getPlugin(QString filename);
    QPluginLoader* getLoader(QString filename);
    QPair<PluginInterface*, QPluginLoader*> getPluginPair(QString filename);
    QMap<QString, QPair<PluginInterface*, QPluginLoader*>> getAllPlugins();

    // Menu (UI) functions
    void inline setToolsMenu(QMenu* menu) { toolsMenu = menu; }
    void inline setFiltersMenu(QMenu *menu) { filtersMenu = menu; }

    // Image manager pointer
    void inline setImageManager(ImageManager* mgr) { image = mgr; }

signals:
    void updateImage();
    void applyChanges();

public slots:
    void execute(QAction *action);
    void execute(QString filename);
    void executeFromMenu();

    // For each plugin
    void update() { emit updateImage(); }
    void apply() { emit applyChanges(); }
    void setImage(QImage* img) { image->setImage(img); }

protected:
    QMap<QString, QPair<PluginInterface*, QPluginLoader*>> plugins;
    QMenu* toolsMenu = nullptr;
    QMenu* filtersMenu = nullptr;
    QActionGroup* actionGroup = nullptr;
    ImageManager* image = nullptr;

};

#endif // PLUGINMANAGER_H
