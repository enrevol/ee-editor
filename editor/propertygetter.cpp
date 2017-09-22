#include "propertygetter.hpp"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
template <class T> using Self = GenericPropertyGetter<T>;

template <class T>
Self<T>::GenericPropertyGetter(const QString& propertyName)
    : propertyName_(propertyName) {}

template <class T> const QString& Self<T>::name() const {
    return propertyName_;
}

template <> bool Self<bool>::get(const NodeGraph& graph) const {
    auto reader = graph.getPropertyReader();
    return reader.getBoolProperty(propertyName_.toStdString());
}

template <> int Self<int>::get(const NodeGraph& graph) const {
    auto reader = graph.getPropertyReader();
    return reader.getIntProperty(propertyName_.toStdString());
}

template <> float Self<float>::get(const NodeGraph& graph) const {
    auto reader = graph.getPropertyReader();
    return reader.getFloatProperty(propertyName_.toStdString());
}

template <> QString Self<QString>::get(const NodeGraph& graph) const {
    auto reader = graph.getPropertyReader();
    return QString::fromStdString(
        reader.getStringProperty(propertyName_.toStdString()));
}

template class GenericPropertyGetter<bool>;
template class GenericPropertyGetter<int>;
template class GenericPropertyGetter<float>;
template class GenericPropertyGetter<QString>;
} // namespace ee
