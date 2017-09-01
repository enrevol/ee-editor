#ifndef EE_PARSER_NODE_LOADER_LIBRARY_HPP
#define EE_PARSER_NODE_LOADER_LIBRARY_HPP

#include <string>
#include <unordered_map>

#include "parserfwd.hpp"

namespace ee {
class NodeLoaderLibrary {
public:
    NodeLoaderLibrary();
    ~NodeLoaderLibrary();

    bool addLoader(const std::string& name, NodeLoaderPtr loader);
    bool removeLoader(const std::string& name);

    const NodeLoaderPtr& getLoader(const std::string& name);

private:
    std::unordered_map<std::string, NodeLoaderPtr> loaders_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_LIBRARY_HPP
