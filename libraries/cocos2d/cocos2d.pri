CONFIG(debug, debug|release) {
    DEFINES += COCOS2D_DEBUG=1
    DEFINES += DEBUG
} else {
    DEFINES += NDEBUG
}

win32:DEFINES += \
    WIN32 \
    _USRDLL \
    _DEBUG \
    _CRT_SECURE_NO_WARNINGS \
    _SCL_SECURE_NO_WARNINGS \
    _USE3DDLL \
    _LIB \
    _WINDOWS \
    LWS_DLL \
    COCOS2DXWIN32_EXPORTS \
    GL_GLEXT_PROTOTYPES \
    _EXPORT_DLL_ \
    _USREXDLL \
    _USEGUIDLL \
    _USRSTUDIODLL \
    PROTOBUF_USE_DLLS \
    LIBPROTOBUF_EXPORTS \
    _WINSOCKAPI_

INCLUDEPATH += \
    $$PWD/cocos \
    $$PWD/cocos/editor-support \
    $$PWD/external

#LIBS += -L$$OUT_PWD/../libraries/cocos2d/ -lcocos2d
#INCLUDEPATH += $$PWD/../libraries/cocos2d
#DEPENDPATH += $$PWD/../libraries/cocos2d
#PRE_TARGETDEPS += $$OUT_PWD/../libraries/cocos2d/libcocos2d.a
