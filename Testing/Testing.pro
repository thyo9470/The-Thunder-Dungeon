QT += core testlib
QT -= gui

CONFIG += qt console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \  
    TestGame.cpp

# Adds the QtQuickSampleLib project path to the header file include lookup path
INCLUDEPATH += $$PWD/../GameLibrary

# Adds the QtQuickSampleLib.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GameLibrary/release/ -lGameLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GameLibrary/debug/ -lGameLibrary

unix {
LIBS += -L$$OUT_PWD/../GameLibrary -lGameLibrary
}
