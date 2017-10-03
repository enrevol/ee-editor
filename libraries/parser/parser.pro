include(../cocos2d/cocos2d.pri)

QT -= gui
QT += opengl

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
    graphreader.hpp \
    widgetloader.hpp \
    layoutloader.hpp \
    property.hpp \
    propertybool.hpp \
    propertyint.hpp \
    propertyfloat.hpp \
    propertystring.hpp \
    propertypoint.hpp \
    propertysize.hpp \
    propertycolor.hpp \
    propertyrect.hpp \
    propertyblend.hpp \
    scale9spriteloader.hpp

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
    graphreader.cpp \
    widgetloader.cpp \
    layoutloader.cpp \
    propertybool.cpp \
    propertyint.cpp \
    propertyfloat.cpp \
    propertystring.cpp \
    propertypoint.cpp \
    propertysize.cpp \
    propertycolor.cpp \
    propertyrect.cpp \
    propertyblend.cpp \
    scale9spriteloader.cpp
