#include <cassert>

#include "skeletonanimationmanager.hpp"

#include <spine/Atlas.h>
#include <spine/Cocos2dAttachmentLoader.h>
#include <spine/SkeletonAnimation.h>
#include <spine/extension.h>

namespace ee {
namespace detail {
struct SpineData {
    explicit SpineData(spSkeletonData* data_, spAttachmentLoader* loader_)
        : data(data_)
        , loader(loader_) {}

    spSkeletonData* data;
    spAttachmentLoader* loader;
};

namespace {
const SpineAtlasDeleter& getAtlasDeleter() {
    static SpineAtlasDeleter deleter = [](spAtlas* atlas) { //
        spAtlas_dispose(atlas);
    };
    return deleter;
}

const SpineDataDeleter& getSkeletonDataDeleter() {
    static SpineDataDeleter deleter = [](SpineData* data) {
        spSkeletonData_dispose(data->data);
        spAttachmentLoader_dispose(data->loader);
    };
    return deleter;
}
} // namespace
} // namespace detail

namespace {
spAtlas* createDummyAtlas() {
    auto self = new spAtlas();
    self->rendererObject = nullptr;
    self->regions = nullptr;

    auto page = spAtlasPage_create(self, "dummy");
    self->pages = page;

    return self;
}

std::string getDummyDataContent() {
    return R"({"bones":[]})";
}
} // namespace

using Self = SkeletonAnimationManager;

const std::string Self::NullAtlasFile = "_____null_atlas_file";
const std::string Self::NullDataFile = "_____null_data_file";

Self& Self::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Self::SkeletonAnimationManager() {}
Self::~SkeletonAnimationManager() {}

spAtlas* Self::getAtlas(const std::string& atlasFile) {
    auto iter = cachedAtlas_.find(atlasFile);
    if (iter == cachedAtlas_.cend()) {
        auto atlas = (atlasFile == NullAtlasFile
                          ? createDummyAtlas()
                          : spAtlas_createFromFile(atlasFile.c_str(), nullptr));
        if (atlas == nullptr) {
            return nullptr;
        }
        auto ptr = detail::SpineAtlasPtr(atlas, detail::getAtlasDeleter());
        iter = cachedAtlas_.emplace(atlasFile, std::move(ptr)).first;
    }
    return iter->second.get();
}

spSkeletonData* Self::getSkeletonData(const std::string& dataFile,
                                      const std::string& atlasFile,
                                      float scale) {
    auto iter = cachedSkeletonData_.find(std::make_pair(dataFile, scale));
    if (iter == cachedSkeletonData_.cend()) {
        auto&& atlas = getAtlas(atlasFile);
        if (atlas == nullptr) {
            return nullptr;
        }
        auto attachmentLoader = &Cocos2dAttachmentLoader_create(atlas)->super;
        auto json = spSkeletonJson_createWithLoader(attachmentLoader);
        json->scale = scale;

        auto skeletonData =
            (dataFile == NullDataFile
                 ? spSkeletonJson_readSkeletonData(
                       json, getDummyDataContent().c_str())
                 : spSkeletonJson_readSkeletonDataFile(json, dataFile.c_str()));
        if (skeletonData == nullptr) {
            spSkeletonJson_dispose(json);
            return nullptr;
        }
        auto ptr = detail::SpineDataPtr(
            new detail::SpineData(skeletonData, attachmentLoader),
            detail::getSkeletonDataDeleter());
        assert(ptr);

        spSkeletonJson_dispose(json);

        iter = cachedSkeletonData_
                   .emplace(std::piecewise_construct,
                            std::forward_as_tuple(dataFile, scale),
                            std::forward_as_tuple(std::move(ptr)))
                   .first;
    }
    return iter->second->data;
}

spSkeletonData* Self::getNullSkeletonData() {
    return getSkeletonData(NullDataFile, NullAtlasFile, 1.0f);
}
} // namespace ee
