#ifndef EE_EDITOR_CC_FILE_UTILS_QT_HPP
#define EE_EDITOR_CC_FILE_UTILS_QT_HPP

#include "platform/CCFileUtils.h"

NS_CC_BEGIN
class FileUtilsQt : public FileUtils {
private:
    using Super = FileUtils;

public:
    virtual bool init() override;

    virtual std::string getWritablePath() const override;

    virtual bool isFileExistInternal(const std::string& path) const override;

    virtual bool isAbsolutePath(const std::string& path) const override;
};
NS_CC_END

#endif // EE_EDITOR_CC_FILE_UTILS_QT_HPP
