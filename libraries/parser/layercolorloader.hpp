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
    static const std::string ClassName;

    /// Constructs a sprite loader.
    LayerColorLoader();

    virtual ~LayerColorLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const override;

    virtual void storeProperties(const cocos2d::Node* node,
                                 PropertyHandler& handler) const override;

    virtual std::string getClassName() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYER_COLOR_LOADER_HPP
