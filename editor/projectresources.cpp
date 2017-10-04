#include "projectresources.hpp"
#include "fileclassifier.hpp"
#include "projectsettings.hpp"
#include "utils.hpp"

#include <2d/CCSpriteFrameCache.h>
#include <base/CCDirector.h>
#include <platform/CCFileUtils.h>
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
            if (info.isDir()) {
                return;
            }
            FileClassifier classifier(info);
            auto path = info.absoluteFilePath();
            if (classifier.isImage()) {
                auto director = cocos2d::Director::getInstance();
                auto cache = director->getTextureCache();
                qDebug() << "Remove image: " << path;
                cache->removeTextureForKey(path.toStdString());
            }
            if (classifier.isSpriteSheet()) {
                auto cache = cocos2d::SpriteFrameCache::getInstance();
                qDebug() << "Remove sheet: " << path;
                cache->removeSpriteFramesFromFile(path.toStdString());
            }
        });
    }
    auto fileUtils = cocos2d::FileUtils::getInstance();
    fileUtils->setSearchPaths({});
    // doneCocosContext();
}

void Self::addResources(const ProjectSettings& settings) {
    makeCocosContext();
    auto&& directories = settings.getResourceDirectories();
    std::vector<std::string> searchPaths;
    for (auto&& path : defaultSearchPaths_) {
        searchPaths.push_back(path.toStdString());
    }
    for (auto&& directory : directories) {
        searchPaths.push_back(directory.absolutePath().toStdString());
        listFiles(directory, [](const QFileInfo& info) {
            if (info.isDir()) {
                return;
            }
            FileClassifier classifier(info);
            auto path = info.absoluteFilePath();
            if (classifier.isImage()) {
                auto director = cocos2d::Director::getInstance();
                auto cache = director->getTextureCache();
                qDebug() << "Add image: " << path;
                cache->addImage(path.toStdString());
            }
            if (classifier.isSpriteSheet()) {
                auto cache = cocos2d::SpriteFrameCache::getInstance();
                qDebug() << "Add sheet: " << path;
                cache->addSpriteFramesWithFile(path.toStdString());
            }
        });
    }
    auto fileUtils = cocos2d::FileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);
    for (auto&& path : searchPaths) {
        qDebug() << "Add search path: " << QString::fromStdString(path);
    }
    // doneCocosContext();
}

void Self::addDefaultSearchPath(const QString& path) {
    defaultSearchPaths_.append(path);
}
} // namespace ee
