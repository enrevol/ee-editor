#ifndef EE_EDITOR_PROPERTY_GETTER_HPP
#define EE_EDITOR_PROPERTY_GETTER_HPP

#include <QString>

namespace ee {
class NodeGraph;

template <class T> class GenericPropertyGetter {
public:
    explicit GenericPropertyGetter(const QString& propertyName);

    const QString& name() const;

    T get(const NodeGraph& graph) const;

private:
    QString propertyName_;
};

using BoolPropertyGetter = GenericPropertyGetter<bool>;
using IntPropertyGetter = GenericPropertyGetter<int>;
using FloatPropertyGetter = GenericPropertyGetter<float>;
using StringPropertyGetter = GenericPropertyGetter<QString>;

template <> bool GenericPropertyGetter<bool>::get(const NodeGraph& graph) const;

template <> int GenericPropertyGetter<int>::get(const NodeGraph& graph) const;

template <>
float GenericPropertyGetter<float>::get(const NodeGraph& graph) const;

template <>
QString GenericPropertyGetter<QString>::get(const NodeGraph& graph) const;
} // namespace ee

#endif // EE_EDITOR_PROPERTY_GETTER_HPP
