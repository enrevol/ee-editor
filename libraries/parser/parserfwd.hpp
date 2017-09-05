#ifndef EE_PARSER_PARSER_FWD_HPP
#define EE_PARSER_PARSER_FWD_HPP

#include <memory>

namespace ee {
class NodeLoader;
using NodeLoaderPtr = std::unique_ptr<NodeLoader>;

class PropertyHandler;
using PropertyHandlerPtr = std::unique_ptr<PropertyHandler>;
} // namespace ee

#endif // EE_PARSER_PARSER_FWD_HPP
