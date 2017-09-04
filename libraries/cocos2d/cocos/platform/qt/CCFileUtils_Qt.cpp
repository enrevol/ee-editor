#include <ciso646>

#include "platform/qt/CCFileUtils_Qt.hpp"

#include <QApplication>
#include <QDir>
#include <QFileInfo>

NS_CC_BEGIN
using Self = FileUtilsQt;

FileUtils* FileUtils::getInstance() {
    if (s_sharedFileUtils == nullptr) {
        s_sharedFileUtils = new Self();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

bool FileUtils::writeValueMapToFile(const ValueMap& dict,
                                    const std::string& fullPath) {
    Q_UNUSED(dict);
    Q_UNUSED(fullPath);
    return false;
}

bool FileUtils::writeValueVectorToFile(const ValueVector& vecData,
                                       const std::string& fullPath) {
    Q_UNUSED(vecData);
    Q_UNUSED(fullPath);
    return false;
}

bool Self::init() {
    QDir execDir(qApp->applicationDirPath());
    QDir resourceDir(execDir);
    resourceDir.cdUp();
    resourceDir.cd("Resources");
    QString path = resourceDir.absolutePath();
    if (not path.endsWith("/", Qt::CaseInsensitive)) {
        path.append("/");
    }
    _defaultResRootPath = path.toStdString();
    return Super::init();
}

std::string Self::getWritablePath() const {
    return qApp->applicationDirPath().toStdString();
}

bool Self::isFileExistInternal(const std::string& path) const {
    if (not isAbsolutePath(path)) {
        return isFileExistInternal(_defaultResRootPath + path);
    }
    QFileInfo info(QString::fromStdString(path));
    return info.exists();
}

bool Self::isAbsolutePath(const std::string& path) const {
    QFileInfo info(QString::fromStdString(path));
    return info.isAbsolute();
}
NS_CC_END
