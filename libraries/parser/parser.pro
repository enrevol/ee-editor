include(../cocos2d/cocos2d.pri)

QT += core gui widgets opengl

TARGET = parser
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++1z

DEFINES += QT_DEPRECATED_WARNINGS

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
    nodeinforeader.hpp \
    nodeinfowriter.hpp \
    propertyreader.hpp \
    propertywriter.hpp \
    layercolorloader.hpp \
    graphreader.hpp

SOURCES += \
    nodeloader.cpp \
    nodeloaderlibrary.cpp \
    propertyhandler.cpp \
    nodegraph.cpp \
    spriteloader.cpp \
    nodeinfo.cpp \
    nodeinforeader.cpp \
    nodeinfowriter.cpp \
    propertyreader.cpp \
    propertywriter.cpp \
    layercolorloader.cpp \
    graphreader.cpp
