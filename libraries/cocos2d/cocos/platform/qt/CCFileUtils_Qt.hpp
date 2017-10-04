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

    virtual ValueMap getValueMapFromFile(const std::string& filename) override;

    virtual ValueMap getValueMapFromData(const char* fileData,
                                         int fileSize) override;

    virtual ValueVector
    getValueVectorFromFile(const std::string& filename) override;

    virtual bool writeToFile(const ValueMap& dict,
                             const std::string& fullPath) override;

protected:
    Value getValueFromData(const char* data, int size);
};
NS_CC_END

#endif // EE_EDITOR_CC_FILE_UTILS_QT_HPP
