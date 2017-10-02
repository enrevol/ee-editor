#include "projectresources.hpp"
#include "projectsettings.hpp"
#include "utils.hpp"

#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>

namespace ee {
using Self = ProjectResources;

namespace {
using FileCallback = std::function<void(const QFileInfo& info)>;

void listFiles(const QFileInfo& info, const FileCallback& callback) {
    callback(info);
    if (info.isDir()) {
        QDir dir(info.absoluteFilePath());
        for (auto&& entry : dir.entryInfoList(QDir::Filter::NoDotAndDotDot |
                                              QDir::Filter::AllEntries)) {
            listFiles(entry, callback);
        }
    }
}

void listFiles(const QDir& dir, const FileCallback& callback) {
    listFiles(QFileInfo(dir.absolutePath()), callback);
}
} // namespace

Self& Self::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Self::ProjectResources() {}
Self::~ProjectResources() {}

void Self::removeResources(const ProjectSettings& settings) {
    makeCocosContext();
    auto&& directories = settings.getResourceDirectories();
    for (auto&& directory : directories) {
        listFiles(directory, [](const QFileInfo& info) {
            if (not info.isDir() && info.suffix() == "png") {
                auto cache =
                    cocos2d::Director::getInstance()->getTextureCache();
                auto path = info.absoluteFilePath();
                qDebug() << "Remove image: " << path;
                cache->removeTextureForKey(path.toStdString());
            }
        });
    }
    // doneCocosContext();
}

void Self::addResources(const ProjectSettings& settings) {
    makeCocosContext();
    auto&& directories = settings.getResourceDirectories();
    for (auto&& directory : directories) {
        listFiles(directory, [](const QFileInfo& info) {
            if (not info.isDir() && info.suffix() == "png") {
                auto cache =
                    cocos2d::Director::getInstance()->getTextureCache();
                auto path = info.absoluteFilePath();
                qDebug() << "Add image: " << path;
                cache->addImage(path.toStdString());
            }
        });
    }
    // doneCocosContext();
}
} // namespace ee
