TEMPLATE = subdirs
SUBDIRS += Game \
    Testing \
    GameLibrary

CONFIG += c++11

Game.depends = GameLibrary
Testing.depends = GameLibrary
