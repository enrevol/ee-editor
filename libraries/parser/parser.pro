include(../cocos2d/cocos2d.pri)

QT -= gui
QT += opengl

TARGET = parser
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++1z

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    ..

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    nodeloader.hpp \
    nodeloaderlibrary.hpp \
    parserfwd.hpp \
    propertyhandler.hpp \
    nodegraph.hpp \
    spriteloader.hpp \
    nodeinfo.hpp \
    layercolorloader.hpp \
    graphreader.hpp \
    widgetloader.hpp \
    layoutloader.hpp \
    property.hpp \
    scale9spriteloader.hpp \
    value.hpp \
    propertytraits.hpp \
    optional.hpp

SOURCES += \
    nodeloader.cpp \
    nodeloaderlibrary.cpp \
    propertyhandler.cpp \
    nodegraph.cpp \
    spriteloader.cpp \
    nodeinfo.cpp \
    layercolorloader.cpp \
    graphreader.cpp \
    widgetloader.cpp \
    layoutloader.cpp \
    scale9spriteloader.cpp \
    value.cpp \
    propertytraits.cpp
