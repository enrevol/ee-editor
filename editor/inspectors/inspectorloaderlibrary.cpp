#include "inspectorloaderlibrary.hpp"
#include "layercolorinspectorloader.hpp"
#include "nodeinspectorloader.hpp"
#include "scale9spriteinspectorloader.hpp"
#include "skeletonanimationinspectorloader.hpp"
#include "spriteinspectorloader.hpp"
#include "widgetinspectorloader.hpp"

#include <QSet>

namespace ee {
using Self = InspectorLoaderLibrary;

Self::InspectorLoaderLibrary() {}
Self::~InspectorLoaderLibrary() {}

void Self::addDefaultLoaders() {
    addLoader(LayerColorInspectorLoader::create());
    addLoader(NodeInspectorLoader::create());
    addLoader(SpriteInspectorLoader::create());
    addLoader(Scale9SpriteInspectorLoader::create());
    addLoader(SkeletonAnimationInspectorLoader::create());
    addLoader(WidgetInspectorLoader::create());
}

bool Self::addLoader(InspectorLoaderPtr loader) {
    return addLoader(loader->getName(), std::move(loader));
}

bool Self::addLoader(const QString& name, InspectorLoaderPtr loader) {
    if (loaders_.count(name) != 0) {
        return false;
    }
    loaders_.emplace(name, std::move(loader));
    return true;
}

QVector<QString> Self::getHierarchy(const QString& name_) const {
    QVector<QString> names;
    auto name = name_;
    while (true) {
        names.push_back(name);
        auto&& loader = getLoader(name);
        if (loader->isRoot()) {
            break;
        }
        name = loader->getParent();
    }
    std::reverse(names.begin(), names.end());
    return names;
}

const InspectorLoaderPtr& Self::getLoader(const QString& name) const {
    Q_ASSERT(loaders_.count(name) != 0);
    return loaders_.at(name);
}

const InspectorLoaderPtr&
Self::getLoader(const QVector<QString>& names_) const {
    auto names = names_;
    std::sort(names.begin(), names.end());
    names.erase(std::unique(names.begin(), names.end()), names.end());

    auto common = names.front();
    auto commonHierarchy = getHierarchy(common);
    for (int i = 1; i < names.size(); ++i) {
        auto&& current = names[i];
        auto&& currentHierarchy = getHierarchy(current);
        for (int j = 0;
             j < commonHierarchy.size() && j < currentHierarchy.size(); ++j) {
            if (commonHierarchy[j] != currentHierarchy[j]) {
                Q_ASSERT(j > 0);
                common = commonHierarchy[j - 1];
                commonHierarchy = getHierarchy(common);
                break;
            }
        }
    }
    return getLoader(common);
}

QVector<Inspector*>
Self::createInspectors(const InspectorLoaderPtr& loader) const {
    QVector<Inspector*> inspectors;
    auto&& hierarchy = getHierarchy(loader->getName());
    for (auto&& name : hierarchy) {
        inspectors.append(getLoader(name)->createInspector());
    }
    return inspectors;
}
} // namespace ee
