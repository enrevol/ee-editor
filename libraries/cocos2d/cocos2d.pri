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

macx:LIBS += \
    -L$$PWD/external/freetype2/prebuilt/mac -lfreetype \
    -L$$PWD/external/jpeg/prebuilt/mac -ljpeg \
    -L$$PWD/external/png/prebuilt/mac -lpng \
    -L$$PWD/external/tiff/prebuilt/mac -ltiff \
    -L$$PWD/external/webp/prebuilt/mac -lwebp \
    -L$$PWD/external/zlib/prebuilt/mac -lz \
    /usr/lib/libiconv.dylib \

win32:LIBS += \
    -L$$PWD/external/freetype2/prebuilt/win32 -lfreetype \
    -L$$PWD/external/jpeg/prebuilt/win32 -ljpeg \
    -L$$PWD/external/png/prebuilt/win32 -lpng \
    -L$$PWD/external/tiff/prebuilt/win32 -ltiff \
    -L$$PWD/external/webp/prebuilt/win32 -lwebp \
    -L$$PWD/external/win32-specific/zlib/prebuilt/win32 -lzlib

#LIBS += -L$$OUT_PWD/../libraries/cocos2d/ -lcocos2d
#INCLUDEPATH += $$PWD/../libraries/cocos2d
#DEPENDPATH += $$PWD/../libraries/cocos2d
#PRE_TARGETDEPS += $$OUT_PWD/../libraries/cocos2d/libcocos2d.a
