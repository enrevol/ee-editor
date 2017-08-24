#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T14:06:59
#
#-------------------------------------------------

QT += core gui widgets opengl

TARGET = cocos2d
TEMPLATE = lib
CONFIG += staticlib

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
cocos \
cocos/editor-support \
external \
external/ConvertUTF \
external/edtaa3func \
external/tinydir \
external/tinyxml2 \
external/unzip \
external/xxhash

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/freetype2
INCLUDEPATH += /usr/local/include/webp

LIBS += -L/usr/local/lib -lwebp
LIBS += -L/usr/local/lib -ltiff
LIBS += -L/usr/local/lib -lpng
LIBS += -L/usr/local/lib -ljpeg
LIBS += -L/usr/local/lib -lfreetype
LIBS += -L/usr/local/lib -lz

SOURCES += \
    cocos/2d/CCAction.cpp \
    cocos/2d/CCActionCamera.cpp \
    cocos/2d/CCActionCatmullRom.cpp \
    cocos/2d/CCActionEase.cpp \
    cocos/2d/CCActionGrid.cpp \
    cocos/2d/CCActionGrid3D.cpp \
    cocos/2d/CCActionInstant.cpp \
    cocos/2d/CCActionInterval.cpp \
    cocos/2d/CCActionManager.cpp \
    cocos/2d/CCActionPageTurn3D.cpp \
    cocos/2d/CCActionProgressTimer.cpp \
    cocos/2d/CCActionTiledGrid.cpp \
    cocos/2d/CCActionTween.cpp \
    cocos/2d/CCAnimation.cpp \
    cocos/2d/CCAnimationCache.cpp \
    cocos/2d/CCAtlasNode.cpp \
    cocos/2d/CCAutoPolygon.cpp \
    cocos/2d/CCCamera.cpp \
    cocos/2d/CCCameraBackgroundBrush.cpp \
    cocos/2d/CCClippingNode.cpp \
    cocos/2d/CCClippingRectangleNode.cpp \
    cocos/2d/CCComponent.cpp \
    cocos/2d/CCComponentContainer.cpp \
    cocos/2d/CCDrawingPrimitives.cpp \
    cocos/2d/CCDrawNode.cpp \
    cocos/2d/CCFastTMXLayer.cpp \
    cocos/2d/CCFastTMXTiledMap.cpp \
    cocos/2d/CCFont.cpp \
    cocos/2d/CCFontAtlas.cpp \
    cocos/2d/CCFontAtlasCache.cpp \
    cocos/2d/CCFontCharMap.cpp \
    cocos/2d/CCFontFNT.cpp \
    cocos/2d/CCFontFreeType.cpp \
    cocos/2d/CCGLBufferedNode.cpp \
    cocos/2d/CCGrabber.cpp \
    cocos/2d/CCGrid.cpp \
    cocos/2d/CCLabel.cpp \
    cocos/2d/CCLabelAtlas.cpp \
    cocos/2d/CCLabelBMFont.cpp \
    cocos/2d/CCLabelTextFormatter.cpp \
    cocos/2d/CCLabelTTF.cpp \
    cocos/2d/CCLayer.cpp \
    cocos/2d/CCLight.cpp \
    cocos/2d/CCMenu.cpp \
    cocos/2d/CCMenuItem.cpp \
    cocos/2d/CCMotionStreak.cpp \
    cocos/2d/CCNode.cpp \
    cocos/2d/CCNodeGrid.cpp \
    cocos/2d/CCParallaxNode.cpp \
    cocos/2d/CCParticleBatchNode.cpp \
    cocos/2d/CCParticleExamples.cpp \
    cocos/2d/CCParticleSystem.cpp \
    cocos/2d/CCParticleSystemQuad.cpp \
    cocos/2d/CCProgressTimer.cpp \
    cocos/2d/CCProtectedNode.cpp \
    cocos/2d/CCRenderTexture.cpp \
    cocos/2d/CCScene.cpp \
    cocos/2d/CCSprite.cpp \
    cocos/2d/CCSpriteBatchNode.cpp \
    cocos/2d/CCSpriteFrame.cpp \
    cocos/2d/CCSpriteFrameCache.cpp \
    cocos/2d/CCTextFieldTTF.cpp \
    cocos/2d/CCTileMapAtlas.cpp \
    cocos/2d/CCTMXLayer.cpp \
    cocos/2d/CCTMXObjectGroup.cpp \
    cocos/2d/CCTMXTiledMap.cpp \
    cocos/2d/CCTMXXMLParser.cpp \
    cocos/2d/CCTransition.cpp \
    cocos/2d/CCTransitionPageTurn.cpp \
    cocos/2d/CCTransitionProgress.cpp \
    cocos/2d/CCTweenFunction.cpp \
    cocos/base/allocator/CCAllocatorDiagnostics.cpp \
    cocos/base/allocator/CCAllocatorGlobal.cpp \
    cocos/base/allocator/CCAllocatorGlobalNewDelete.cpp \
    cocos/base/atitc.cpp \
    cocos/base/base64.cpp \
    cocos/base/CCAsyncTaskPool.cpp \
    cocos/base/CCAutoreleasePool.cpp \
    cocos/base/ccCArray.cpp \
    cocos/base/CCConfiguration.cpp \
    cocos/base/CCConsole.cpp \
    cocos/base/CCController-android.cpp \
    cocos/base/CCController.cpp \
    cocos/base/CCData.cpp \
    cocos/base/CCDataVisitor.cpp \
    cocos/base/CCDirector.cpp \
    cocos/base/CCEvent.cpp \
    cocos/base/CCEventAcceleration.cpp \
    cocos/base/CCEventController.cpp \
    cocos/base/CCEventCustom.cpp \
    cocos/base/CCEventDispatcher.cpp \
    cocos/base/CCEventFocus.cpp \
    cocos/base/CCEventKeyboard.cpp \
    cocos/base/CCEventListener.cpp \
    cocos/base/CCEventListenerAcceleration.cpp \
    cocos/base/CCEventListenerController.cpp \
    cocos/base/CCEventListenerCustom.cpp \
    cocos/base/CCEventListenerFocus.cpp \
    cocos/base/CCEventListenerKeyboard.cpp \
    cocos/base/CCEventListenerMouse.cpp \
    cocos/base/CCEventListenerTouch.cpp \
    cocos/base/CCEventMouse.cpp \
    cocos/base/CCEventTouch.cpp \
    cocos/base/CCIMEDispatcher.cpp \
    cocos/base/CCNinePatchImageParser.cpp \
    cocos/base/CCNS.cpp \
    cocos/base/CCProfiling.cpp \
    cocos/base/CCProperties.cpp \
    cocos/base/ccRandom.cpp \
    cocos/base/CCRef.cpp \
    cocos/base/CCScheduler.cpp \
    cocos/base/CCScriptSupport.cpp \
    cocos/base/CCStencilStateManager.cpp \
    cocos/base/CCTouch.cpp \
    cocos/base/ccTypes.cpp \
    cocos/base/CCUserDefault.cpp \
    cocos/base/ccUTF8.cpp \
    cocos/base/ccUtils.cpp \
    cocos/base/CCValue.cpp \
    cocos/base/etc1.cpp \
    cocos/base/ObjectFactory.cpp \
    cocos/base/pvr.cpp \
    cocos/base/s3tc.cpp \
    cocos/base/TGAlib.cpp \
    cocos/base/ZipUtils.cpp \
    cocos/editor-support/spine/AttachmentVertices.cpp \
    cocos/editor-support/spine/Cocos2dAttachmentLoader.cpp \
    cocos/editor-support/spine/SkeletonAnimation.cpp \
    cocos/editor-support/spine/SkeletonBatch.cpp \
    cocos/editor-support/spine/SkeletonRenderer.cpp \
    cocos/editor-support/spine/spine-cocos2dx.cpp \
    cocos/math/CCAffineTransform.cpp \
    cocos/math/CCGeometry.cpp \
    cocos/math/CCVertex.cpp \
    cocos/math/Mat4.cpp \
    cocos/math/Mat4.inl \
    cocos/math/MathUtil.cpp \
    cocos/math/MathUtil.inl \
    cocos/math/MathUtilNeon.inl \
    cocos/math/MathUtilNeon64.inl \
    cocos/math/MathUtilSSE.inl \
    cocos/math/Quaternion.cpp \
    cocos/math/Quaternion.inl \
    cocos/math/TransformUtils.cpp \
    cocos/math/Vec2.cpp \
    cocos/math/Vec2.inl \
    cocos/math/Vec3.cpp \
    cocos/math/Vec3.inl \
    cocos/math/Vec4.cpp \
    cocos/math/Vec4.inl \
    cocos/platform/CCFileUtils.cpp \
    cocos/platform/CCGLView.cpp \
    cocos/platform/CCImage.cpp \
    cocos/platform/CCSAXParser.cpp \
    cocos/platform/CCThread.cpp \
    cocos/renderer/CCBatchCommand.cpp \
    cocos/renderer/CCCustomCommand.cpp \
    cocos/renderer/CCFrameBuffer.cpp \
    cocos/renderer/CCGLProgram.cpp \
    cocos/renderer/CCGLProgramCache.cpp \
    cocos/renderer/CCGLProgramState.cpp \
    cocos/renderer/CCGLProgramStateCache.cpp \
    cocos/renderer/ccGLStateCache.cpp \
    cocos/renderer/CCGroupCommand.cpp \
    cocos/renderer/CCMaterial.cpp \
    cocos/renderer/CCMeshCommand.cpp \
    cocos/renderer/CCPass.cpp \
    cocos/renderer/CCPrimitive.cpp \
    cocos/renderer/CCPrimitiveCommand.cpp \
    cocos/renderer/CCQuadCommand.cpp \
    cocos/renderer/CCRenderCommand.cpp \
    cocos/renderer/CCRenderer.cpp \
    cocos/renderer/CCRenderState.cpp \
    cocos/renderer/ccShaders.cpp \
    cocos/renderer/CCTechnique.cpp \
    cocos/renderer/CCTexture2D.cpp \
    cocos/renderer/CCTextureAtlas.cpp \
    cocos/renderer/CCTextureCache.cpp \
    cocos/renderer/CCTextureCube.cpp \
    cocos/renderer/CCTrianglesCommand.cpp \
    cocos/renderer/CCVertexAttribBinding.cpp \
    cocos/renderer/CCVertexIndexBuffer.cpp \
    cocos/renderer/CCVertexIndexData.cpp \
    cocos/ui/CocosGUI.cpp \
    cocos/ui/UIAbstractCheckButton.cpp \
    cocos/ui/UIButton.cpp \
    cocos/ui/UICheckBox.cpp \
    cocos/ui/UIDeprecated.cpp \
    cocos/ui/UIHBox.cpp \
    cocos/ui/UIHelper.cpp \
    cocos/ui/UIImageView.cpp \
    cocos/ui/UILayout.cpp \
    cocos/ui/UILayoutComponent.cpp \
    cocos/ui/UILayoutManager.cpp \
    cocos/ui/UILayoutParameter.cpp \
    cocos/ui/UIListView.cpp \
    cocos/ui/UILoadingBar.cpp \
    cocos/ui/UIPageView.cpp \
    cocos/ui/UIPageViewIndicator.cpp \
    cocos/ui/UIRadioButton.cpp \
    cocos/ui/UIRelativeBox.cpp \
    cocos/ui/UIRichText.cpp \
    cocos/ui/UIScale9Sprite.cpp \
    cocos/ui/UIScrollView.cpp \
    cocos/ui/UIScrollViewBar.cpp \
    cocos/ui/UISlider.cpp \
    cocos/ui/UITabControl.cpp \
    cocos/ui/UIText.cpp \
    cocos/ui/UITextAtlas.cpp \
    cocos/ui/UITextBMFont.cpp \
    cocos/ui/UITextField.cpp \
    cocos/ui/UIVBox.cpp \
    cocos/ui/UIWidget.cpp \
    cocos/cocos2d.cpp \
    cocos/base/ccFPSImages.c \
    cocos/editor-support/spine/Animation.c \
    cocos/editor-support/spine/AnimationState.c \
    cocos/editor-support/spine/AnimationStateData.c \
    cocos/editor-support/spine/Atlas.c \
    cocos/editor-support/spine/AtlasAttachmentLoader.c \
    cocos/editor-support/spine/Attachment.c \
    cocos/editor-support/spine/AttachmentLoader.c \
    cocos/editor-support/spine/Bone.c \
    cocos/editor-support/spine/BoneData.c \
    cocos/editor-support/spine/BoundingBoxAttachment.c \
    cocos/editor-support/spine/Event.c \
    cocos/editor-support/spine/EventData.c \
    cocos/editor-support/spine/extension.c \
    cocos/editor-support/spine/IkConstraint.c \
    cocos/editor-support/spine/IkConstraintData.c \
    cocos/editor-support/spine/Json.c \
    cocos/editor-support/spine/MeshAttachment.c \
    cocos/editor-support/spine/PathAttachment.c \
    cocos/editor-support/spine/PathConstraint.c \
    cocos/editor-support/spine/PathConstraintData.c \
    cocos/editor-support/spine/RegionAttachment.c \
    cocos/editor-support/spine/Skeleton.c \
    cocos/editor-support/spine/SkeletonBinary.c \
    cocos/editor-support/spine/SkeletonBounds.c \
    cocos/editor-support/spine/SkeletonData.c \
    cocos/editor-support/spine/SkeletonJson.c \
    cocos/editor-support/spine/Skin.c \
    cocos/editor-support/spine/Slot.c \
    cocos/editor-support/spine/SlotData.c \
    cocos/editor-support/spine/TransformConstraint.c \
    cocos/editor-support/spine/TransformConstraintData.c \
    cocos/editor-support/spine/VertexAttachment.c \
    cocos/base/CCController-apple.mm \
    cocos/editor-support/cocostudio/CocosStudioExtension.cpp \
    external/clipper/clipper.cpp \
    external/clipper/clipper.cpp \
    external/poly2tri/common/shapes.cc \
    external/poly2tri/sweep/advancing_front.cc \
    external/poly2tri/sweep/cdt.cc \
    external/poly2tri/sweep/sweep.cc \
    external/poly2tri/sweep/sweep_context.cc \
    cocos/3d/CCFrustum.cpp \
    cocos/3d/CCAABB.cpp \
    cocos/3d/CCAnimate3D.cpp \
    cocos/3d/CCAnimation3D.cpp \
    cocos/3d/CCAnimationCurve.inl \
    cocos/3d/CCAttachNode.cpp \
    cocos/3d/CCBillBoard.cpp \
    cocos/3d/CCBundle3D.cpp \
    cocos/3d/CCBundleReader.cpp \
    cocos/3d/CCFrustum.cpp \
    cocos/3d/CCMesh.cpp \
    cocos/3d/CCMeshSkin.cpp \
    cocos/3d/CCMeshVertexIndexData.cpp \
    cocos/3d/CCMotionStreak3D.cpp \
    cocos/3d/CCOBB.cpp \
    cocos/3d/CCObjLoader.cpp \
    cocos/3d/CCPlane.cpp \
    cocos/3d/CCRay.cpp \
    cocos/3d/CCSkeleton3D.cpp \
    cocos/3d/CCSkybox.cpp \
    cocos/3d/CCSprite3D.cpp \
    cocos/3d/CCSprite3DMaterial.cpp \
    cocos/3d/CCTerrain.cpp \
    external/edtaa3func/edtaa3func.cpp \
    cocos/deprecated/CCArray.cpp \
    cocos/deprecated/CCDeprecated.cpp \
    cocos/deprecated/CCDictionary.cpp \
    cocos/deprecated/CCNotificationCenter.cpp \
    cocos/deprecated/CCSet.cpp \
    cocos/deprecated/CCString.cpp \
    external/tinyxml2/tinyxml2.cpp \
    external/ConvertUTF/ConvertUTFWrapper.cpp \
    external/ConvertUTF/ConvertUTF.c \
    external/md5/md5.c \
    external/unzip/ioapi.cpp \
    external/unzip/ioapi_mem.cpp \
    external/unzip/unzip.cpp \
    cocos/platform/qt/CCApplication_Qt.cpp \
    cocos/platform/qt/CCCommon_Qt.cpp \
    cocos/platform/qt/CCDevice_Qt.cpp \
    cocos/platform/qt/CCFileUtils_Qt.cpp \
    cocos/platform/qt/CCGLView_Qt.cpp \
    cocos/platform/qt/CCOpenGLWidget_Qt.cpp \
    cocos/platform/qt/CCGLView_Qt.cpp \
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
    external/xxhash/xxhash.c \
    cocos/platform/qt/CCUserDefault_Qt.cpp

HEADERS += \
    cocos/2d/CCAction.h \
    cocos/2d/CCActionCamera.h \
    cocos/2d/CCActionCatmullRom.h \
    cocos/2d/CCActionEase.h \
    cocos/2d/CCActionGrid.h \
    cocos/2d/CCActionGrid3D.h \
    cocos/2d/CCActionInstant.h \
    cocos/2d/CCActionInterval.h \
    cocos/2d/CCActionManager.h \
    cocos/2d/CCActionPageTurn3D.h \
    cocos/2d/CCActionProgressTimer.h \
    cocos/2d/CCActionTiledGrid.h \
    cocos/2d/CCActionTween.h \
    cocos/2d/CCAnimation.h \
    cocos/2d/CCAnimationCache.h \
    cocos/2d/CCAtlasNode.h \
    cocos/2d/CCAutoPolygon.h \
    cocos/2d/CCCamera.h \
    cocos/2d/CCCameraBackgroundBrush.h \
    cocos/2d/CCClippingNode.h \
    cocos/2d/CCClippingRectangleNode.h \
    cocos/2d/CCComponent.h \
    cocos/2d/CCComponentContainer.h \
    cocos/2d/CCDrawingPrimitives.h \
    cocos/2d/CCDrawNode.h \
    cocos/2d/CCFastTMXLayer.h \
    cocos/2d/CCFastTMXTiledMap.h \
    cocos/2d/CCFont.h \
    cocos/2d/CCFontAtlas.h \
    cocos/2d/CCFontAtlasCache.h \
    cocos/2d/CCFontCharMap.h \
    cocos/2d/CCFontFNT.h \
    cocos/2d/CCFontFreeType.h \
    cocos/2d/CCGLBufferedNode.h \
    cocos/2d/CCGrabber.h \
    cocos/2d/CCGrid.h \
    cocos/2d/CCLabel.h \
    cocos/2d/CCLabelAtlas.h \
    cocos/2d/CCLabelBMFont.h \
    cocos/2d/CCLabelTextFormatter.h \
    cocos/2d/CCLabelTTF.h \
    cocos/2d/CCLayer.h \
    cocos/2d/CCLight.h \
    cocos/2d/CCMenu.h \
    cocos/2d/CCMenuItem.h \
    cocos/2d/CCMotionStreak.h \
    cocos/2d/CCNode.h \
    cocos/2d/CCNodeGrid.h \
    cocos/2d/CCParallaxNode.h \
    cocos/2d/CCParticleBatchNode.h \
    cocos/2d/CCParticleExamples.h \
    cocos/2d/CCParticleSystem.h \
    cocos/2d/CCParticleSystemQuad.h \
    cocos/2d/CCProgressTimer.h \
    cocos/2d/CCProtectedNode.h \
    cocos/2d/CCRenderTexture.h \
    cocos/2d/CCScene.h \
    cocos/2d/CCSprite.h \
    cocos/2d/CCSpriteBatchNode.h \
    cocos/2d/CCSpriteFrame.h \
    cocos/2d/CCSpriteFrameCache.h \
    cocos/2d/CCTextFieldTTF.h \
    cocos/2d/CCTileMapAtlas.h \
    cocos/2d/CCTMXLayer.h \
    cocos/2d/CCTMXObjectGroup.h \
    cocos/2d/CCTMXTiledMap.h \
    cocos/2d/CCTMXXMLParser.h \
    cocos/2d/CCTransition.h \
    cocos/2d/CCTransitionPageTurn.h \
    cocos/2d/CCTransitionProgress.h \
    cocos/2d/CCTweenFunction.h \
    cocos/base/allocator/CCAllocatorBase.h \
    cocos/base/allocator/CCAllocatorDiagnostics.h \
    cocos/base/allocator/CCAllocatorGlobal.h \
    cocos/base/allocator/CCAllocatorMacros.h \
    cocos/base/allocator/CCAllocatorMutex.h \
    cocos/base/allocator/CCAllocatorStrategyDefault.h \
    cocos/base/allocator/CCAllocatorStrategyFixedBlock.h \
    cocos/base/allocator/CCAllocatorStrategyGlobalSmallBlock.h \
    cocos/base/allocator/CCAllocatorStrategyPool.h \
    cocos/base/atitc.h \
    cocos/base/base64.h \
    cocos/base/CCAsyncTaskPool.h \
    cocos/base/CCAutoreleasePool.h \
    cocos/base/ccCArray.h \
    cocos/base/ccConfig.h \
    cocos/base/CCConfiguration.h \
    cocos/base/CCConsole.h \
    cocos/base/CCController.h \
    cocos/base/CCData.h \
    cocos/base/CCDataVisitor.h \
    cocos/base/CCDirector.h \
    cocos/base/CCEvent.h \
    cocos/base/CCEventAcceleration.h \
    cocos/base/CCEventController.h \
    cocos/base/CCEventCustom.h \
    cocos/base/CCEventDispatcher.h \
    cocos/base/CCEventFocus.h \
    cocos/base/CCEventKeyboard.h \
    cocos/base/CCEventListener.h \
    cocos/base/CCEventListenerAcceleration.h \
    cocos/base/CCEventListenerController.h \
    cocos/base/CCEventListenerCustom.h \
    cocos/base/CCEventListenerFocus.h \
    cocos/base/CCEventListenerKeyboard.h \
    cocos/base/CCEventListenerMouse.h \
    cocos/base/CCEventListenerTouch.h \
    cocos/base/CCEventMouse.h \
    cocos/base/CCEventTouch.h \
    cocos/base/CCEventType.h \
    cocos/base/ccFPSImages.h \
    cocos/base/CCGameController.h \
    cocos/base/CCIMEDelegate.h \
    cocos/base/CCIMEDispatcher.h \
    cocos/base/ccMacros.h \
    cocos/base/CCMap.h \
    cocos/base/CCNinePatchImageParser.h \
    cocos/base/CCNS.h \
    cocos/base/CCProfiling.h \
    cocos/base/CCProperties.h \
    cocos/base/CCProtocols.h \
    cocos/base/ccRandom.h \
    cocos/base/CCRef.h \
    cocos/base/CCRefPtr.h \
    cocos/base/CCScheduler.h \
    cocos/base/CCScriptSupport.h \
    cocos/base/CCStencilStateManager.h \
    cocos/base/CCTouch.h \
    cocos/base/ccTypes.h \
    cocos/base/CCUserDefault.h \
    cocos/base/ccUTF8.h \
    cocos/base/ccUtils.h \
    cocos/base/CCValue.h \
    cocos/base/CCVector.h \
    cocos/base/etc1.h \
    cocos/base/firePngData.h \
    cocos/base/ObjectFactory.h \
    cocos/base/pvr.h \
    cocos/base/s3tc.h \
    cocos/base/TGAlib.h \
    cocos/base/uthash.h \
    cocos/base/utlist.h \
    cocos/base/ZipUtils.h \
    cocos/editor-support/spine/Animation.h \
    cocos/editor-support/spine/AnimationState.h \
    cocos/editor-support/spine/AnimationStateData.h \
    cocos/editor-support/spine/Atlas.h \
    cocos/editor-support/spine/AtlasAttachmentLoader.h \
    cocos/editor-support/spine/Attachment.h \
    cocos/editor-support/spine/AttachmentLoader.h \
    cocos/editor-support/spine/AttachmentVertices.h \
    cocos/editor-support/spine/Bone.h \
    cocos/editor-support/spine/BoneData.h \
    cocos/editor-support/spine/BoundingBoxAttachment.h \
    cocos/editor-support/spine/Cocos2dAttachmentLoader.h \
    cocos/editor-support/spine/Event.h \
    cocos/editor-support/spine/EventData.h \
    cocos/editor-support/spine/extension.h \
    cocos/editor-support/spine/IkConstraint.h \
    cocos/editor-support/spine/IkConstraintData.h \
    cocos/editor-support/spine/Json.h \
    cocos/editor-support/spine/kvec.h \
    cocos/editor-support/spine/MeshAttachment.h \
    cocos/editor-support/spine/PathAttachment.h \
    cocos/editor-support/spine/PathConstraint.h \
    cocos/editor-support/spine/PathConstraintData.h \
    cocos/editor-support/spine/RegionAttachment.h \
    cocos/editor-support/spine/Skeleton.h \
    cocos/editor-support/spine/SkeletonAnimation.h \
    cocos/editor-support/spine/SkeletonBatch.h \
    cocos/editor-support/spine/SkeletonBinary.h \
    cocos/editor-support/spine/SkeletonBounds.h \
    cocos/editor-support/spine/SkeletonData.h \
    cocos/editor-support/spine/SkeletonJson.h \
    cocos/editor-support/spine/SkeletonRenderer.h \
    cocos/editor-support/spine/Skin.h \
    cocos/editor-support/spine/Slot.h \
    cocos/editor-support/spine/SlotData.h \
    cocos/editor-support/spine/spine-cocos2dx.h \
    cocos/editor-support/spine/spine.h \
    cocos/editor-support/spine/TransformConstraint.h \
    cocos/editor-support/spine/TransformConstraintData.h \
    cocos/editor-support/spine/VertexAttachment.h \
    cocos/math/CCAffineTransform.h \
    cocos/math/CCGeometry.h \
    cocos/math/CCMath.h \
    cocos/math/CCMathBase.h \
    cocos/math/CCVertex.h \
    cocos/math/Mat4.h \
    cocos/math/MathUtil.h \
    cocos/math/Quaternion.h \
    cocos/math/TransformUtils.h \
    cocos/math/Vec2.h \
    cocos/math/Vec3.h \
    cocos/math/Vec4.h \
    cocos/platform/CCApplication.h \
    cocos/platform/CCApplicationProtocol.h \
    cocos/platform/CCCommon.h \
    cocos/platform/CCDevice.h \
    cocos/platform/CCFileUtils.h \
    cocos/platform/CCGLView.h \
    cocos/platform/CCImage.h \
    cocos/platform/CCPlatformConfig.h \
    cocos/platform/CCPlatformDefine.h \
    cocos/platform/CCPlatformMacros.h \
    cocos/platform/CCSAXParser.h \
    cocos/platform/CCStdC.h \
    cocos/platform/CCThread.h \
    cocos/renderer/CCBatchCommand.h \
    cocos/renderer/CCCustomCommand.h \
    cocos/renderer/CCFrameBuffer.h \
    cocos/renderer/CCGLProgram.h \
    cocos/renderer/CCGLProgramCache.h \
    cocos/renderer/CCGLProgramState.h \
    cocos/renderer/CCGLProgramStateCache.h \
    cocos/renderer/ccGLStateCache.h \
    cocos/renderer/CCGroupCommand.h \
    cocos/renderer/CCMaterial.h \
    cocos/renderer/CCMeshCommand.h \
    cocos/renderer/CCPass.h \
    cocos/renderer/CCPrimitive.h \
    cocos/renderer/CCPrimitiveCommand.h \
    cocos/renderer/CCQuadCommand.h \
    cocos/renderer/CCRenderCommand.h \
    cocos/renderer/CCRenderCommandPool.h \
    cocos/renderer/CCRenderer.h \
    cocos/renderer/CCRenderState.h \
    cocos/renderer/ccShaders.h \
    cocos/renderer/CCTechnique.h \
    cocos/renderer/CCTexture2D.h \
    cocos/renderer/CCTextureAtlas.h \
    cocos/renderer/CCTextureCache.h \
    cocos/renderer/CCTextureCube.h \
    cocos/renderer/CCTrianglesCommand.h \
    cocos/renderer/CCVertexAttribBinding.h \
    cocos/renderer/CCVertexIndexBuffer.h \
    cocos/renderer/CCVertexIndexData.h \
    cocos/ui/CocosGUI.h \
    cocos/ui/GUIDefine.h \
    cocos/ui/GUIExport.h \
    cocos/ui/UIAbstractCheckButton.h \
    cocos/ui/UIButton.h \
    cocos/ui/UICheckBox.h \
    cocos/ui/UIDeprecated.h \
    cocos/ui/UIHBox.h \
    cocos/ui/UIHelper.h \
    cocos/ui/UIImageView.h \
    cocos/ui/UILayout.h \
    cocos/ui/UILayoutComponent.h \
    cocos/ui/UILayoutManager.h \
    cocos/ui/UILayoutParameter.h \
    cocos/ui/UIListView.h \
    cocos/ui/UILoadingBar.h \
    cocos/ui/UIPageView.h \
    cocos/ui/UIPageViewIndicator.h \
    cocos/ui/UIRadioButton.h \
    cocos/ui/UIRelativeBox.h \
    cocos/ui/UIRichText.h \
    cocos/ui/UIScale9Sprite.h \
    cocos/ui/UIScrollView.h \
    cocos/ui/UIScrollViewBar.h \
    cocos/ui/UISlider.h \
    cocos/ui/UITabControl.h \
    cocos/ui/UIText.h \
    cocos/ui/UITextAtlas.h \
    cocos/ui/UITextBMFont.h \
    cocos/ui/UITextField.h \
    cocos/ui/UIVBox.h \
    cocos/ui/UIWidget.h \
    cocos/cocos2d.h \
    cocos/editor-support/cocostudio/CocosStudioExtension.h \
    external/clipper/clipper.hpp \
    external/clipper/clipper.hpp \
    external/poly2tri/common/shapes.h \
    external/poly2tri/common/utils.h \
    external/poly2tri/sweep/advancing_front.h \
    external/poly2tri/sweep/cdt.h \
    external/poly2tri/sweep/sweep.h \
    external/poly2tri/sweep/sweep_context.h \
    external/poly2tri/poly2tri.h \
    cocos/3d/CCFrustum.h \
    cocos/3d/CCAABB.h \
    cocos/3d/CCAnimate3D.h \
    cocos/3d/CCAnimation3D.h \
    cocos/3d/CCAnimationCurve.h \
    cocos/3d/CCAttachNode.h \
    cocos/3d/CCBillBoard.h \
    cocos/3d/CCBundle3D.h \
    cocos/3d/CCBundle3DData.h \
    cocos/3d/CCBundleReader.h \
    cocos/3d/CCFrustum.h \
    cocos/3d/CCMesh.h \
    cocos/3d/CCMeshSkin.h \
    cocos/3d/CCMeshVertexIndexData.h \
    cocos/3d/CCMotionStreak3D.h \
    cocos/3d/CCOBB.h \
    cocos/3d/CCObjLoader.h \
    cocos/3d/CCPlane.h \
    cocos/3d/CCRay.h \
    cocos/3d/CCSkeleton3D.h \
    cocos/3d/CCSkybox.h \
    cocos/3d/CCSprite3D.h \
    cocos/3d/CCSprite3DMaterial.h \
    cocos/3d/CCTerrain.h \
    cocos/3d/cocos3d.h \
    external/edtaa3func/edtaa3func.h \
    cocos/deprecated/CCArray.h \
    cocos/deprecated/CCBool.h \
    cocos/deprecated/CCDeprecated.h \
    cocos/deprecated/CCDictionary.h \
    cocos/deprecated/CCDouble.h \
    cocos/deprecated/CCFloat.h \
    cocos/deprecated/CCInteger.h \
    cocos/deprecated/CCNotificationCenter.h \
    cocos/deprecated/CCSet.h \
    cocos/deprecated/CCString.h \
    external/tinyxml2/tinyxml2.h \
    external/ConvertUTF/ConvertUTF.h \
    external/md5/md5.h \
    external/unzip/crypt.h \
    external/unzip/ioapi.h \
    external/unzip/ioapi_mem.h \
    external/unzip/unzip.h \
    cocos/platform/qt/CCApplication_Qt.hpp \
    cocos/platform/qt/CCGLView_Qt.hpp \
    cocos/platform/qt/CCOpenGLWidget_Qt.hpp \
    cocos/platform/mac/CCStdC-mac.h \
    cocos/platform/qt/CCGLView_Qt.hpp \
    cocos/platform/CCGL.h \
    external/tinydir/tinydir.h \
    external/clipper/clipper.hpp \
    external/ConvertUTF/ConvertUTF.h \
    external/edtaa3func/edtaa3func.h \
    external/md5/md5.h \
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
    external/xxtea/xxtea.h \
    cocos/platform/qt/CCUserDefault_Qt.hpp \
    cocos/platform/qt/CCFileUtils_Qt.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
