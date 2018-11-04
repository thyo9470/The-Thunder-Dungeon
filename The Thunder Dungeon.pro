TEMPLATE = subdirs
SUBDIRS += Game \
    Testing \
    GameLibrary

Game.depends = GameLibrary
Testing.depends = GameLibrary
