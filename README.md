QImageViewer
============

A simple example how to create image browser for desktop in Qt 5.  
Feature list:
* Open and save files in JPG, GIF, PNG, BMP (QImage native support)
* Recent files list
* Zoom, move and select built-in tools
* Tools and filters in plugins, loaded by QPluginLoader

Build program
-------------
Build it like any Qt project - open `.pro` file in *Qt Creator* and set path. I recommend to set directory **above** project directory, for example `../build`

Build plugins
-------------
Open `.pro` file in Qt Creator, but configure build directory as `plugins/tools` or `plugins/filters` **inside** your program build directory, for example - for filters - it will be `../build/plugins/filters`. Good luck!
