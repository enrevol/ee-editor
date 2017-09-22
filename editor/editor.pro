include(../libraries/cocos2d/cocos2d.pri)

QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11

CONFIG += c++1z
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    ../libraries

LIBS += \
    -L$$OUT_PWD/../libraries/cocos2d -lcocos2d \
    -L$$OUT_PWD/../libraries/parser -lparser

PRE_TARGETDEPS += \
    $$OUT_PWD/../libraries/parser/libparser.a

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    projectsettings.cpp \
    projectsettingsdialog.cpp \
    config.cpp \
    settings.cpp \
    contentprotectionkey.cpp \
    iserializable.cpp \
    appdelegate.cpp \
    openglwidget.cpp \
    rootscene.cpp \
    utils.cpp \
    glsledit.cpp \
    glslhighlighter.cpp \
    glsleditsidebar.cpp \
    inspectortexture.cpp \
    inspectorfloat.cpp \
    scenetree.cpp \
    inspectorpoint.cpp \
    interfacesettings.cpp \
    filesystemwatcher.cpp \
    resourcetree.cpp \
    imageview.cpp \
    scenetreemodel.cpp \
    scenetreeitem.cpp \
    nodehighlighter.cpp \
    nodeinspector.cpp \
    inspectorcontainer.cpp \
    inspector.cpp \
    inspectorlistwidget.cpp \
    inspectorbool.cpp \
    selectionpath.cpp \
    selectiontree.cpp \
    propertygetter.cpp \
    inspectorscale.cpp

HEADERS += \
    mainwindow.hpp \
    projectsettings.hpp \
    projectsettingsdialog.hpp \
    config.hpp \
    optional.hpp \
    settings.hpp \
    contentprotectionkey.hpp \
    iserializable.hpp \
    appdelegate.hpp \
    openglwidget.hpp \
    rootscene.hpp \
    utils.hpp \
    glsledit.hpp \
    glslhighlighter.hpp \
    glslcomponent.hpp \
    glsleditsidebar.hpp \
    inspectortexture.hpp \
    inspectorfloat.hpp \
    scenetree.hpp \
    inspectorpoint.hpp \
    interfacesettings.hpp \
    filesystemwatcher.hpp \
    resourcetree.hpp \
    imageview.hpp \
    scenetreemodel.hpp \
    scenetreeitem.hpp \
    nodehighlighter.hpp \
    nodeinspector.hpp \
    inspectorcontainer.hpp \
    inspector.hpp \
    inspectorlistwidget.hpp \
    inspectorbool.hpp \
    selectionpath.hpp \
    selectiontree.hpp \
    propertygetter.hpp \
    inspectorscale.hpp

FORMS += \
    mainwindow.ui \
    projectsettingsdialog.ui \
    inspectortexture.ui \
    inspectorfloat.ui \
    inspectorpoint.ui \
    inspectorbool.ui \
    inspectorscale.ui
