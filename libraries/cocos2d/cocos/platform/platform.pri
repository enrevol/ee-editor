COCOS2DX_ROOT=$$PWD/../..

SOURCES += \
    $$COCOS2DX_ROOT/cocos/platform/CCFileUtils.cpp \
    $$COCOS2DX_ROOT/cocos/platform/CCGLView.cpp \
    $$COCOS2DX_ROOT/cocos/platform/CCImage.cpp \
    $$COCOS2DX_ROOT/cocos/platform/CCSAXParser.cpp \
    $$COCOS2DX_ROOT/cocos/platform/CCThread.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCApplication_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCCommon_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCDevice_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCFileUtils_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCGLView_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCOpenGLWidget_Qt.cpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCUserDefault_Qt.cpp

HEADERS += \
    $$COCOS2DX_ROOT/cocos/platform/CCApplication.h \
    $$COCOS2DX_ROOT/cocos/platform/CCApplicationProtocol.h \
    $$COCOS2DX_ROOT/cocos/platform/CCCommon.h \
    $$COCOS2DX_ROOT/cocos/platform/CCDevice.h \
    $$COCOS2DX_ROOT/cocos/platform/CCFileUtils.h \
    $$COCOS2DX_ROOT/cocos/platform/CCGL.h \
    $$COCOS2DX_ROOT/cocos/platform/CCGLView.h \
    $$COCOS2DX_ROOT/cocos/platform/CCImage.h \
    $$COCOS2DX_ROOT/cocos/platform/CCPlatformConfig.h \
    $$COCOS2DX_ROOT/cocos/platform/CCPlatformDefine.h \
    $$COCOS2DX_ROOT/cocos/platform/CCPlatformMacros.h \
    $$COCOS2DX_ROOT/cocos/platform/CCSAXParser.h \
    $$COCOS2DX_ROOT/cocos/platform/CCStdC.h \
    $$COCOS2DX_ROOT/cocos/platform/CCThread.h \
    $$COCOS2DX_ROOT/cocos/platform/mac/CCStdC-mac.h \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCApplication_Qt.hpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCFileUtils_Qt.hpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCGLView_Qt.hpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCOpenGLWidget_Qt.hpp \
    $$COCOS2DX_ROOT/cocos/platform/qt/CCUserDefault_Qt.hpp \
    $$COCOS2DX_ROOT/cocos/platform/win32/CCStdC-win32.h
