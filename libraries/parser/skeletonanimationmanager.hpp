#ifndef EE_PARSER_SKELETON_ANIMATION_MANAGER_HPP
#define EE_PARSER_SKELETON_ANIMATION_MANAGER_HPP

#include <functional>
#include <map>
#include <memory>
#include <string>

struct spAtlas;
struct spSkeletonData;

namespace ee {
namespace detail {
struct SpineData;

using SpineAtlasDeleter = std::function<void(spAtlas* atlas)>;
using SpineAtlasPtr = std::unique_ptr<spAtlas, SpineAtlasDeleter>;
using SpineDataDeleter = std::function<void(SpineData* data)>;
using SpineDataPtr = std::unique_ptr<SpineData, SpineDataDeleter>;
} // namespace detail

class SkeletonAnimationManager {
private:
    using Self = SkeletonAnimationManager;

public:
    static Self& getInstance();

    spAtlas* getAtlas(const std::string& atlasFile);

    spSkeletonData* getSkeletonData(const std::string& dataFile,
                                    const std::string& atlasFile, float scale);

protected:
    SkeletonAnimationManager();
    ~SkeletonAnimationManager();

    SkeletonAnimationManager(const Self&) = delete;
    Self& operator=(const Self&) = delete;

private:
    std::map<std::string, detail::SpineAtlasPtr> cachedAtlas_;

    std::map<std::pair<std::string, float>, detail::SpineDataPtr>
        cachedSkeletonData_;
};
} // namespace ee

#endif // EE_PARSER_SKELETON_ANIMATION_MANAGER_HPP
