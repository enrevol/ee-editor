#ifndef EE_PARSER_NODE_LOADER_LIBRARY_HPP
#define EE_PARSER_NODE_LOADER_LIBRARY_HPP

#include <string>
#include <unordered_map>

#include "parserfwd.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
/// A collection of node loaders.
class NodeLoaderLibrary final {
private:
    using Self = NodeLoaderLibrary;

public:
    NodeLoaderLibrary();
    ~NodeLoaderLibrary();

    NodeLoaderLibrary(const Self& other);

    void addDefaultLoaders();

    cocos2d::Node* createNode(const std::string& name) const;

    /// Checks whether this library has a loader for the specified class name.
    /// @param name The name of the node loader.
    bool hasLoader(const std::string& name) const;

    /// Adds a node loader with the specified name.
    /// @param name The name of the node loader.
    /// @param loader The desired loader.
    /// @return True if the addition was succesful, false if there is an
    /// exist loader whose the same name.
    bool addLoader(const std::string& name, NodeLoaderPtr loader);

    /// Removes a node loader whose the specified name.
    /// @param name The name of the node loader.
    /// @return True if the removing was successful, false otherwise.
    bool removeLoader(const std::string& name);

    /// Gets the node loader whose the specified name.
    /// @param name The name of the node loader.
    const NodeLoaderPtr& getLoader(const std::string& name) const;

private:
    std::unordered_map<std::string, NodeLoaderPtr> loaders_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_LIBRARY_HPP
