#include "pluginmanager.h"

PluginManager::PluginManager(QObject *parent) :
    QObject(parent)
{
    // Create QActionGroup and connect it
    actionGroup = new QActionGroup(0);
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(execute(QAction*)));
}

PluginManager::~PluginManager() {
    this->unloadAll();
    delete actionGroup;
}

void PluginManager::loadAll() {
    // Clear menus
    if (toolsMenu)
        toolsMenu->clear();
    if (filtersMenu)
        filtersMenu->clear();

    // File filter
    QStringList filenameFilters;
    #ifdef __linux
        filenameFilters << "*.so";
    #elif _WIN32
        filenameFilters << "*.dll";
    #endif

    // Set tools directory
    QDir pluginsDir("plugins");
    qDebug() << "Loading plugins from" << pluginsDir.absolutePath();

    // Iterate over files
    unsigned int toolsCount = 0, filtersCount = 0;
    QDirIterator it(pluginsDir.absolutePath(), filenameFilters, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filename = it.next();

        // Ignore files without "tool" and "filter" in name
        if (!filename.toLower().contains("tool") && !filename.toLower().contains("filter"))
            continue;

        // Try to load
        if (this->load(filename)) {
            // Increase counters
            if (filename.toLower().contains("tool"))
                toolsCount++;
            else if (filename.toLower().contains("filter"))
                filtersCount++;
        }
    }

    // Insert element when plugin count is zero
    QAction* emptyAction;
    if (toolsCount == 0)
        emptyAction = toolsMenu->addAction("No tools loaded");
    else if (filtersCount == 0)
        emptyAction = filtersMenu->addAction("No filters loaded");

    // Disable newly created element
    emptyAction->setDisabled(true);

    // Debug info
    qDebug() << "Loaded" << toolsCount << "tools and" << filtersCount << "filters";
}

bool PluginManager::load(QString filename) {
    // Empty filename protection
    if (filename.isEmpty())
        return false;

    // Try to load
    QDir path(filename);
    QPluginLoader *loader = new QPluginLoader(path.absoluteFilePath(filename));
    QObject *pluginInstance = loader->instance();

    // Check if plugin loaded into QPluginLoader
    if (!pluginInstance) {
        qDebug() << "Can't' load filter plugin from file" << filename;
        qDebug() << "Error:" << loader->errorString();
        return false;
    }

    // Cast QObject to plugin
    PluginInterface *plugin = qobject_cast<PluginInterface*>(pluginInstance);

    // Check if loaded correctly
    if (!plugin) {
        qDebug() << "Failed to load plugin" << filename;
        return false;
    }

    // Connect plugins signals (PluginManager will route signals outside)
    connect(plugin, SIGNAL(applyChanges()), this, SLOT(apply()));
    connect(plugin, SIGNAL(updateImage()), this, SLOT(update()));
    connect(plugin, SIGNAL(setImage(QImage*)), this, SLOT(setImage(QImage*)));

    // Add plugin to QMap
    plugins[filename] = qMakePair<PluginInterface*, QPluginLoader*>(plugin, loader);

    // Get type of plugin
    PluginType ptype = plugin->getType();

    // Check if can add action to menu (is menu set)
    if ( (ptype == TOOL) && !toolsMenu)
        return true;
    if ( (ptype == FILTER) && !filtersMenu)
        return true;

    // Create menu action
    QString pluginName = plugin->getPluginName();
    QAction *menuAction;

    // Add it to menu
    if (ptype == TOOL)
        menuAction = toolsMenu->addAction(tr(pluginName.toStdString().c_str()));
    else if (ptype == FILTER)
        menuAction = filtersMenu->addAction(tr(pluginName.toStdString().c_str()));

    // Set data in our QAction
    QVariant pluginVariant = qVariantFromValue((void*)plugin);
    menuAction->setData(pluginVariant);

    // Set QActionGroup (no need individual connections)
    menuAction->setActionGroup(actionGroup);

    // Successfull!
    return true;
}

void PluginManager::unloadAll() {
    // Foreach over map and call unload(filename) on each
    for (auto e: plugins.keys()) {
        this->unload(e);
    }
}

bool PluginManager::unload(QString filename) {
    // Check if loaded
    if (!plugins[filename].first || !plugins[filename].second)
        return false;

    // Call assigned QPluginLoader
    plugins[filename].second->unload();
    delete plugins[filename].second;

    // Delete QMap entry
    plugins.remove(filename);

    return true;
}

PluginInterface* PluginManager::getPlugin(QString filename) {
    return plugins[filename].first;
}

QPluginLoader* PluginManager::getLoader(QString filename) {
    return plugins[filename].second;
}

QPair<PluginInterface*, QPluginLoader*> PluginManager::getPluginPair(QString filename) {
    return plugins[filename];
}

QMap<QString, QPair<PluginInterface*, QPluginLoader*>> PluginManager::getAllPlugins() {
    return plugins;
}

void PluginManager::execute(QAction *action) {
    // Get value from QAction and cast it to PluginInterface
    QVariant v = action->data();
    PluginInterface* plugin = (PluginInterface*)v.value<void*>();

    // If plugin is invalid or image not set
    if (!plugin || !image)
        return;

    // Call plugin
    plugin->execute(image->get());
}

void PluginManager::execute(QString filename) {
    // Check plugin and image
    if (!plugins[filename].first || !image)
        return;

    // Call plugin
    plugins[filename].first->execute(image->get());
}

void PluginManager::executeFromMenu() {
    // Get sender
    QAction *action = qobject_cast<QAction *>(sender());

    // Call execute(QAction)
    this->execute(action);
}
