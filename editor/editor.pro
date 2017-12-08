include(../libraries/cocos2d/cocos2d.pri)

QT += opengl
QT += xml

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
        -L$$OUT_PWD/../libraries/parser -lparser \
        -L$$OUT_PWD/../libraries/qtplist -lqtplist

    PRE_TARGETDEPS += \
        $$OUT_PWD/../libraries/cocos2d/libcocos2d.a \
        $$OUT_PWD/../libraries/parser/libparser.a \
        $$OUT_PWD/../libraries/qtplist/libqtplist.a
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


FORMS += \
    inspectors/inspectorbool.ui \
    inspectors/inspectorcolor.ui \
    inspectors/inspectorfloat.ui \
    inspectors/inspectorfloatxy.ui \
    inspectors/inspectorgroup.ui \
    inspectors/inspectorint.ui \
    inspectors/inspectorintslider.ui \
    inspectors/inspectorscale.ui \
    inspectors/inspectorselect.ui \
    inspectors/inspectorstring.ui \
    inspectors/inspectortexture.ui \
    mainwindow.ui \
    projectsettingsdialog.ui \
    inspectors/inspectorblend.ui

SUBDIRS += \
    editor.pro

DISTFILES += \
    res/gizmo_box.png \
    res/gizmo_box_hovered.png \
    res/gizmo_box_locked.png \
    res/gizmo_x_axis.png \
    res/gizmo_x_axis_hovered.png \
    res/gizmo_x_axis_locked.png \
    res/gizmo_y_axis.png \
    res/gizmo_y_axis_hovered.png \
    res/gizmo_y_axis_locked.png \
    res/selection_box_hovered.png \
    res/selection_box_locked.png

HEADERS += \
    inspectors/inspector.hpp \
    inspectors/inspectorblend.hpp \
    inspectors/inspectorbool.hpp \
    inspectors/inspectorcolor.hpp \
    inspectors/inspectorfloat.hpp \
    inspectors/inspectorfloatxy.hpp \
    inspectors/inspectorgroup.hpp \
    inspectors/inspectorint.hpp \
    inspectors/inspectorintslider.hpp \
    inspectors/inspectorlistwidget.hpp \
    inspectors/inspectorloader.hpp \
    inspectors/inspectorloaderlibrary.hpp \
    inspectors/inspectorscale.hpp \
    inspectors/inspectorselect.hpp \
    inspectors/inspectorstring.hpp \
    inspectors/inspectortexture.hpp \
    inspectors/layercolorinspectorloader.hpp \
    inspectors/nodeinspector.hpp \
    inspectors/nodeinspectorloader.hpp \
    inspectors/scale9spriteinspector.hpp \
    inspectors/scale9spriteinspectorloader.hpp \
    inspectors/spriteinspector.hpp \
    inspectors/spriteinspectorloader.hpp \
    inspectors/widgetinspector.hpp \
    inspectors/widgetinspectorloader.hpp \
    scene/gizmo.hpp \
    scene/nodehighlighter.hpp \
    scene/nodehighlighterlayer.hpp \
    scene/openglwidget.hpp \
    scenetree/scenetreeitem.hpp \
    scenetree/scenetreemodel.hpp \
    selection/selectionpath.hpp \
    selection/selectiontree.hpp \
    appdelegate.hpp \
    clickablewidget.hpp \
    config.hpp \
    contentprotectionkey.hpp \
    fileclassifier.hpp \
    filesystemwatcher.hpp \
    glslcomponent.hpp \
    glsledit.hpp \
    glsleditsidebar.hpp \
    glslhighlighter.hpp \
    imageview.hpp \
    interfacesettings.hpp \
    iserializable.hpp \
    mainwindow.hpp \
    projectresources.hpp \
    projectsettings.hpp \
    projectsettingsdialog.hpp \
    resourcetree.hpp \
    settings.hpp \
    spritesheet.hpp \
    utils.hpp \
    scenemanager.hpp \
    scenetree/scenetreeview.hpp \
    scenetree/scenetree.hpp \
    scene/mainscene.hpp \
    scene/mainsceneview.hpp \
    inspectors/inspectorlist.hpp \
    optional.hpp \
    scene/rulerview.hpp \
    scene/rulerline.hpp

SOURCES += \
    inspectors/inspector.cpp \
    inspectors/inspectorblend.cpp \
    inspectors/inspectorbool.cpp \
    inspectors/inspectorcolor.cpp \
    inspectors/inspectorfloat.cpp \
    inspectors/inspectorfloatxy.cpp \
    inspectors/inspectorgroup.cpp \
    inspectors/inspectorint.cpp \
    inspectors/inspectorintslider.cpp \
    inspectors/inspectorlistwidget.cpp \
    inspectors/inspectorloader.cpp \
    inspectors/inspectorloaderlibrary.cpp \
    inspectors/inspectorscale.cpp \
    inspectors/inspectorselect.cpp \
    inspectors/inspectorstring.cpp \
    inspectors/inspectortexture.cpp \
    inspectors/layercolorinspectorloader.cpp \
    inspectors/nodeinspector.cpp \
    inspectors/nodeinspectorloader.cpp \
    inspectors/scale9spriteinspector.cpp \
    inspectors/scale9spriteinspectorloader.cpp \
    inspectors/spriteinspector.cpp \
    inspectors/spriteinspectorloader.cpp \
    inspectors/widgetinspector.cpp \
    inspectors/widgetinspectorloader.cpp \
    scene/gizmo.cpp \
    scene/nodehighlighter.cpp \
    scene/nodehighlighterlayer.cpp \
    scene/openglwidget.cpp \
    scenetree/scenetreeitem.cpp \
    scenetree/scenetreemodel.cpp \
    selection/selectionpath.cpp \
    selection/selectiontree.cpp \
    appdelegate.cpp \
    clickablewidget.cpp \
    config.cpp \
    contentprotectionkey.cpp \
    fileclassifier.cpp \
    filesystemwatcher.cpp \
    glsledit.cpp \
    glsleditsidebar.cpp \
    glslhighlighter.cpp \
    imageview.cpp \
    interfacesettings.cpp \
    iserializable.cpp \
    main.cpp \
    mainwindow.cpp \
    projectresources.cpp \
    projectsettings.cpp \
    projectsettingsdialog.cpp \
    resourcetree.cpp \
    settings.cpp \
    spritesheet.cpp \
    utils.cpp \
    scenemanager.cpp \
    scenetree/scenetreeview.cpp \
    scenetree/scenetree.cpp \
    scene/mainscene.cpp \
    scene/mainsceneview.cpp \
    inspectors/inspectorlist.cpp \
    scene/rulerview.cpp \
    scene/rulerline.cpp
