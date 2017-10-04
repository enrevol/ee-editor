#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T14:06:59
#
#-------------------------------------------------

include(cocos2d.pri)
include(cocos/2d/2d.pri)
include(cocos/base/base.pri)
include(cocos/deprecated/deprecated.pri)
include(cocos/editor-support/spine/spine.pri)
include(cocos/math/math.pri)
include(cocos/platform/platform.pri)
include(cocos/renderer/renderer.pri)
include(cocos/ui/ui.pri)

QT += opengl
QT += xml

TARGET = cocos2d
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    external/ConvertUTF \
    external/edtaa3func \
    external/tinydir \
    external/tinyxml2 \
    external/unzip \
    external/xxhash \
    ..

macx:INCLUDEPATH += \
    external/freetype2/include/mac/freetype2 \
    external/jpeg/include/mac \
    external/png/include/mac \
    external/tiff/include/mac \
    external/webp/include/mac \
    external/zlib/include

win32:INCLUDEPATH += \
    external/freetype2/include/win32/freetype2 \
    external/jpeg/include/win32 \
    external/png/include/win32 \
    external/tiff/include/win32 \
    external/webp/include/win32 \
    external/win32-specific/zlib/include

# win32:LIBS += \
#    -Lexternal/freetype2/prebuilt/win32 -lfreetype \
#    -Lexternal/win32-specific/prebuilt -zlib

# win32:!win32-g++: PRE_TARGETDEPS += $$PWD/external/freetype2/prebuilt/win10/x64/freetype.lib
# else:macx|win32-g++: PRE_TARGETDEPS += $$PWD/external/freetype2/prebuilt/win10/x64/libfreetype.a

SOURCES += \
    cocos/cocos2d.cpp \
    cocos/editor-support/cocostudio/CocosStudioExtension.cpp \
    external/clipper/clipper.cpp \
    external/ConvertUTF/ConvertUTFWrapper.cpp \
    external/edtaa3func/edtaa3func.cpp \
    external/poly2tri/common/shapes.cc \
    external/poly2tri/sweep/advancing_front.cc \
    external/poly2tri/sweep/cdt.cc \
    external/poly2tri/sweep/sweep.cc \
    external/poly2tri/sweep/sweep_context.cc \
    external/tinyxml2/tinyxml2.cpp \
    external/unzip/ioapi.cpp \
    external/unzip/ioapi_mem.cpp \
    external/unzip/unzip.cpp \
    external/xxtea/xxtea.cpp \
    external/ConvertUTF/ConvertUTF.c \
    external/md5/md5.c \
    external/xxhash/xxhash.c

HEADERS += \
    cocos/cocos2d.h \
    cocos/editor-support/cocostudio/CocosStudioExtension.h \
    external/clipper/clipper.hpp \
    external/ConvertUTF/ConvertUTF.h \
    external/edtaa3func/edtaa3func.h \
    external/md5/md5.h \
    external/poly2tri/poly2tri.h \
    external/poly2tri/common/shapes.h \
    external/poly2tri/common/utils.h \
    external/poly2tri/sweep/advancing_front.h \
    external/poly2tri/sweep/cdt.h \
    external/poly2tri/sweep/sweep.h \
    external/poly2tri/sweep/sweep_context.h \
    external/poly2tri/poly2tri.h \
    external/rapidxml/rapidxml.hpp \
    external/rapidxml/rapidxml_iterators.hpp \
    external/rapidxml/rapidxml_print.hpp \
    external/rapidxml/rapidxml_sax3.hpp \
    external/rapidxml/rapidxml_utils.hpp \
    external/tinydir/tinydir.h \
    external/tinyxml2/tinyxml2.h \
    external/unzip/crypt.h \
    external/unzip/ioapi.h \
    external/unzip/ioapi_mem.h \
    external/unzip/unzip.h \
    external/xxhash/xxhash.h \
    external/xxtea/xxtea.h

DISTFILES += \
    cocos/renderer/ccShader_3D_Color.frag \
    cocos/renderer/ccShader_3D_ColorNormal.frag \
    cocos/renderer/ccShader_3D_ColorNormalTex.frag \
    cocos/renderer/ccShader_3D_ColorTex.frag \
    cocos/renderer/ccShader_3D_Particle.frag \
    cocos/renderer/ccShader_3D_Skybox.frag \
    cocos/renderer/ccShader_3D_Terrain.frag \
    cocos/renderer/ccShader_CameraClear.frag \
    cocos/renderer/ccShader_ETC1AS_PositionTextureColor.frag \
    cocos/renderer/ccShader_ETC1AS_PositionTextureGray.frag \
    cocos/renderer/ccShader_Label_df.frag \
    cocos/renderer/ccShader_Label_df_glow.frag \
    cocos/renderer/ccShader_Label_normal.frag \
    cocos/renderer/ccShader_Label_outline.frag \
    cocos/renderer/ccShader_Position_uColor.frag \
    cocos/renderer/ccShader_PositionColor.frag \
    cocos/renderer/ccShader_PositionColorLengthTexture.frag \
    cocos/renderer/ccShader_PositionTexture.frag \
    cocos/renderer/ccShader_PositionTexture_uColor.frag \
    cocos/renderer/ccShader_PositionTextureA8Color.frag \
    cocos/renderer/ccShader_PositionTextureColor.frag \
    cocos/renderer/ccShader_PositionTextureColor_noMVP.frag \
    cocos/renderer/ccShader_PositionTextureColorAlphaTest.frag \
    cocos/renderer/ccShader_UI_Gray.frag \
    cocos/renderer/ccShader_3D_Particle.vert \
    cocos/renderer/ccShader_3D_PositionNormalTex.vert \
    cocos/renderer/ccShader_3D_PositionTex.vert \
    cocos/renderer/ccShader_3D_Skybox.vert \
    cocos/renderer/ccShader_3D_Terrain.vert \
    cocos/renderer/ccShader_CameraClear.vert \
    cocos/renderer/ccShader_Label.vert \
    cocos/renderer/ccShader_Position_uColor.vert \
    cocos/renderer/ccShader_PositionColor.vert \
    cocos/renderer/ccShader_PositionColorLengthTexture.vert \
    cocos/renderer/ccShader_PositionColorTextureAsPointsize.vert \
    cocos/renderer/ccShader_PositionTexture.vert \
    cocos/renderer/ccShader_PositionTexture_uColor.vert \
    cocos/renderer/ccShader_PositionTextureA8Color.vert \
    cocos/renderer/ccShader_PositionTextureColor.vert \
    cocos/renderer/ccShader_PositionTextureColor_noMVP.vert
