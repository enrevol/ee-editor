#ifndef EE_PARSER_LAYER_COLOR_LOADER_HPP
#define EE_PARSER_LAYER_COLOR_LOADER_HPP

#include "nodeloader.hpp"

namespace ee {
class LayerColorLoader : public NodeLoader {
public:
private:
    using Self = LayerColorLoader;
    using Super = NodeLoader;

public:
    static NodeLoaderPtr create();

    virtual ~LayerColorLoader() override;

    virtual cocos2d::Node* createNode() const override;

protected:
    /// Constructs a sprite loader.
    LayerColorLoader();

    virtual void addReadHandlers(PropertyHandler& handler) override;
    virtual void addWriteHandlers(PropertyHandler& handler) override;
    virtual void addDefaultProperties(PropertyWriter& writer) override;

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYER_COLOR_LOADER_HPP
