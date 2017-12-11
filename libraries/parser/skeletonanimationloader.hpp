#ifndef EE_PARSER_SKELETION_ANIMATION_LOADER_HPP
#define EE_PARSER_SKELETION_ANIMATION_LOADER_HPP

#include "nodeloader.hpp"

namespace spine {
class SkeletonAnimation;
} // namespace spine

namespace ee {
class SkeletonAnimationLoader : public NodeLoader {
private:
    using Super = NodeLoader;
    using Self = SkeletonAnimationLoader;
    using Target = spine::SkeletonAnimation;

public:
    struct Property {
        static const PropertyString DataFile;
        static const PropertyString AtlasFile;
        static const PropertyFloat AnimationScale;
        static const PropertyString Animation;
        static const PropertyString Skin;
        static const PropertyBool Loop;
        static const PropertyFloat TimeScale;
        static const PropertyBlend BlendFunc;
        static const PropertyBool DebugBones;
        static const PropertyBool DebugSlots;
    };

    static const std::string ClassName;

    SkeletonAnimationLoader();

    ~SkeletonAnimationLoader();

    virtual std::string getClassName() const override;

    virtual cocos2d::Node* createNode() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_SKELETION_ANIMATION_LOADER_HPP
