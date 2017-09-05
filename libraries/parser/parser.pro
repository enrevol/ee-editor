include(../cocos2d/cocos2d.pri)

QT += core gui widgets opengl

TARGET = parser
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    nodeloader.hpp \
    nodeloaderlibrary.hpp \
    parserfwd.hpp \
    editorreader.hpp \
    propertyhandler.hpp

SOURCES += \
    nodeloader.cpp \
    nodeloaderlibrary.cpp \
    editorreader.cpp \
    propertyhandler.cpp
