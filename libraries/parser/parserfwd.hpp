#ifndef EE_PARSER_PARSER_FWD_HPP
#define EE_PARSER_PARSER_FWD_HPP

#include <map>
#include <memory>
#include <vector>

namespace cocos2d {
struct BlendFunc;
struct Color3B;
class Node;
class Sprite;
class Vec2;
using Point = Vec2;
class Rect;
class Size;
class Value;
} // namespace cocos2d

namespace spine {
class SkeletonAnimation;
} // namespace spine

namespace ee {
class NodeLoader;
using NodeLoaderPtr = std::unique_ptr<NodeLoader>;

class NodeInfoReader;
class NodeInfoWriter;

class Property;
class PropertyHandler;
class PropertyReader;
class PropertyWriter;

template <class Value>
class GenericProperty;

using PropertyBool = GenericProperty<bool>;
using PropertyInt = GenericProperty<int>;
using PropertyFloat = GenericProperty<float>;
using PropertyString = GenericProperty<std::string>;

template <class Enum>
using PropertyEnum = GenericProperty<Enum>;

using PropertyBlend = GenericProperty<cocos2d::BlendFunc>;
using PropertyColor3B = GenericProperty<cocos2d::Color3B>;
using PropertyPoint = GenericProperty<cocos2d::Point>;
using PropertyRect = GenericProperty<cocos2d::Rect>;
using PropertySize = GenericProperty<cocos2d::Size>;

class Value;

using ValueList = std::vector<Value>;
using ValueMap = std::map<std::string, Value>;
} // namespace ee

#endif // EE_PARSER_PARSER_FWD_HPP
