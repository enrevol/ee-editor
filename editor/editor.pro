QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app

CONFIG += c++1z
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11

LIBS += /usr/local/lib/libjpeg.a
LIBS += /usr/local/lib/libpng.a
LIBS += /usr/local/lib/libwebp.a
LIBS += /usr/local/lib/libtiff.a
LIBS += /usr/local/lib/libfreetype.a
LIBS += /usr/local/opt/zlib/lib/libz.a
LIBS += /usr/lib/libiconv.dylib
LIBS += /usr/lib/libbz2.dylib

INCLUDEPATH += \
    ../libraries \
    ../libraries/cocos2d/cocos \
    ../libraries/cocos2d/cocos/editor-support \
    ../libraries/cocos2d/external

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    projectsettings.cpp \
    projectsettingsdialog.cpp \
    config.cpp \
    settings.cpp \
    contentprotectionkey.cpp \
    iserializable.cpp \
    appdelegate.cpp

HEADERS += \
    mainwindow.hpp \
    projectsettings.hpp \
    projectsettingsdialog.hpp \
    config.hpp \
    optional.hpp \
    settings.hpp \
    contentprotectionkey.hpp \
    iserializable.hpp \
    appdelegate.hpp

FORMS += \
    mainwindow.ui \
    projectsettingsdialog.ui

COCOS2DX_ROOT=$$PWD/../libraries/cocos2d

LIBS += -L$$OUT_PWD/../libraries/cocos2d/ -lcocos2d
INCLUDEPATH += $$PWD/../libraries/cocos2d
DEPENDPATH += $$PWD/../libraries/cocos2d
PRE_TARGETDEPS += $$OUT_PWD/../libraries/cocos2d/libcocos2d.a
