QT += core testlib
QT -= gui

CONFIG += qt console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \  
    TestGame.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GameLibrary/release/ -lGameLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GameLibrary/debug/ -lGameLibrary
else:unix: LIBS += -L$$OUT_PWD/../GameLibrary/ -lGameLibrary

INCLUDEPATH += $$PWD/../GameLibrary
DEPENDPATH += $$PWD/../GameLibrary

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GameLibrary/release/GameLibrary.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GameLibrary/debug/GameLibrary.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../GameLibrary/usr/lib/libGameLibrary.a
