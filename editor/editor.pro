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

mac {
    LIBS += \
        -L$$OUT_PWD/../libraries/cocos2d -lcocos2d \
        -L$$OUT_PWD/../libraries/parser -lparser

    PRE_TARGETDEPS += \
        $$OUT_PWD/../libraries/cocos2d/libcocos2d.a \
        $$OUT_PWD/../libraries/parser/libparser.a
}

win32 {
    CONFIG(debug, debug|release) {
        LIBS += \
            -L$$OUT_PWD/../libraries/cocos2d/debug -lcocos2d \
            -L$$OUT_PWD/../libraries/parser/debug -lparser

        PRE_TARGETDEPS += \
            $$OUT_PWD/../libraries/cocos2d/debug/cocos2d.lib \
            $$OUT_PWD/../libraries/parser/debug/parser.lib
    }
    CONFIG(release, debug|release) {
        LIBS += \
            -L$$OUT_PWD/../libraries/cocos2d/release -lcocos2d \
            -L$$OUT_PWD/../libraries/parser/release -lparser

        PRE_TARGETDEPS += \
            $$OUT_PWD/../libraries/cocos2d/release/cocos2d.lib \
            $$OUT_PWD/../libraries/parser/release/parser.lib
    }
}

RESOURCES += \
    editor.qrc

mac {
    cocos_images.path = Contents/Resources/cocos_images
    cocos_images.files = $$files($$PWD/res/*.png)

    QMAKE_BUNDLE_DATA += \
        cocos_images
}

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
    interfacesettings.cpp \
    filesystemwatcher.cpp \
    resourcetree.cpp \
    imageview.cpp \
    scenetreemodel.cpp \
    scenetreeitem.cpp \
    nodehighlighter.cpp \
    nodeinspector.cpp \
    inspector.cpp \
    inspectorlistwidget.cpp \
    inspectorbool.cpp \
    selectionpath.cpp \
    selectiontree.cpp \
    propertygetter.cpp \
    inspectorscale.cpp \
    inspectorfloatxy.cpp \
    inspectorint.cpp \
    inspectorcolor.cpp \
    clickablewidget.cpp \
    inspectorgroup.cpp \
    spriteinspector.cpp \
    inspectorstring.cpp \
    widgetinspector.cpp \
    inspectorintslider.cpp \
    gizmo.cpp \
    nodehighlighterlayer.cpp \
    nodeinspectorloader.cpp \
    inspectorloader.cpp \
    widgetinspectorloader.cpp \
    inspectorloaderlibrary.cpp \
    layercolorinspectorloader.cpp \
    spriteinspectorloader.cpp \
    projectresources.cpp \
    inspectorblend.cpp \
    inspectorselect.cpp \
    scale9spriteinspector.cpp \
    scale9spriteinspectorloader.cpp

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
    interfacesettings.hpp \
    filesystemwatcher.hpp \
    resourcetree.hpp \
    imageview.hpp \
    scenetreemodel.hpp \
    scenetreeitem.hpp \
    nodehighlighter.hpp \
    nodeinspector.hpp \
    inspector.hpp \
    inspectorlistwidget.hpp \
    inspectorbool.hpp \
    selectionpath.hpp \
    selectiontree.hpp \
    propertygetter.hpp \
    inspectorscale.hpp \
    inspectorfloatxy.hpp \
    inspectorint.hpp \
    inspectorcolor.hpp \
    clickablewidget.hpp \
    inspectorgroup.hpp \
    spriteinspector.hpp \
    inspectorstring.hpp \
    widgetinspector.hpp \
    inspectorintslider.hpp \
    gizmo.hpp \
    nodehighlighterlayer.hpp \
    nodeinspectorloader.hpp \
    inspectorloader.hpp \
    widgetinspectorloader.hpp \
    inspectorloaderlibrary.hpp \
    layercolorinspectorloader.hpp \
    spriteinspectorloader.hpp \
    projectresources.hpp \
    inspectorblend.hpp \
    inspectorselect.hpp \
    scale9spriteinspector.hpp \
    scale9spriteinspectorloader.hpp

FORMS += \
    mainwindow.ui \
    projectsettingsdialog.ui \
    inspectortexture.ui \
    inspectorfloat.ui \
    inspectorbool.ui \
    inspectorscale.ui \
    inspectorfloatxy.ui \
    inspectorint.ui \
    inspectorcolor.ui \
    inspectorgroup.ui \
    inspectorstring.ui \
    inspectorintslider.ui \
    inspectorblend.ui \
    inspectorselect.ui
