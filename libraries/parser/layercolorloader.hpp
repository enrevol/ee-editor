#ifndef EE_PARSER_LAYER_COLOR_LOADER_HPP
#define EE_PARSER_LAYER_COLOR_LOADER_HPP

#include "nodeloader.hpp"

namespace cocos2d {
class LayerColor;
} // namespace cocos2d

namespace ee {
class LayerColorLoader : public NodeLoader {
public:
private:
    using Self = LayerColorLoader;
    using Super = NodeLoader;
    using Target = cocos2d::LayerColor;

public:
    static const std::string Name;

    /// Constructs a sprite loader.
    LayerColorLoader();

    virtual ~LayerColorLoader() override;

    /// @see Super.
    virtual std::string getName() const override;

    /// @see Super.
    virtual cocos2d::Node* createNode() const override;

protected:
    /// @see Super.
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYER_COLOR_LOADER_HPP
