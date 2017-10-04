#include <ciso646>

#include "platform/qt/CCFileUtils_Qt.hpp"

#include <qtplist/plistparser.h>
#include <qtplist/plistserializer.h>

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

NS_CC_BEGIN
using Self = FileUtilsQt;

FileUtils* FileUtils::getInstance() {
    if (s_sharedFileUtils == nullptr) {
        s_sharedFileUtils = new Self();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

namespace {
cocos2d::Value convertToValue(const QJsonValue& json) {
    if (json.isBool()) {
        return cocos2d::Value(json.toBool());
    }
    if (json.isDouble()) {
        auto v = json.toDouble();
        constexpr auto eps = std::numeric_limits<double>::epsilon();
        if (std::abs(int(v) - v) < eps) {
            return cocos2d::Value(json.toInt());
        }
        return cocos2d::Value(static_cast<float>(json.toDouble()));
    }
    if (json.isString()) {
        return cocos2d::Value(json.toString().toStdString());
    }
    if (json.isArray()) {
        cocos2d::ValueVector array;
        for (auto v : json.toArray()) {
            array.push_back(convertToValue(v));
        }
        return cocos2d::Value(array);
    }
    if (json.isObject()) {
        cocos2d::ValueMap dict;
        auto obj = json.toObject();
        for (auto iter = obj.begin(); iter != obj.end(); ++iter) {
            dict.emplace(iter.key().toStdString(),
                         convertToValue(iter.value()));
        }
        return cocos2d::Value(dict);
    }
    Q_ASSERT(false);
    return cocos2d::Value::Null;
}

QJsonValue convertToJson(const cocos2d::Value& value) {
    if (value.getType() == cocos2d::Value::Type::BOOLEAN) {
        return value.asBool();
    }
    if (value.getType() == cocos2d::Value::Type::INTEGER) {
        return value.asInt();
    }
    if (value.getType() == cocos2d::Value::Type::FLOAT) {
        return static_cast<double>(value.asFloat());
    }
    if (value.getType() == cocos2d::Value::Type::STRING) {
        return QString::fromStdString(value.asString());
    }
    if (value.getType() == cocos2d::Value::Type::VECTOR) {
        QJsonArray array;
        for (auto&& v : value.asValueVector()) {
            array.append(convertToJson(v));
        }
        return array;
    }
    if (value.getType() == cocos2d::Value::Type::MAP) {
        QJsonObject dict;
        for (auto&& v : value.asValueMap()) {
            dict.insert(QString::fromStdString(v.first),
                        convertToJson(v.second));
        }
        return dict;
    }
    Q_ASSERT(false);
    return QJsonValue::Null;
}
} // namespace

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
    auto type = QStandardPaths::StandardLocation::DocumentsLocation;
    return QStandardPaths::writableLocation(type).toStdString();
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

ValueMap Self::getValueMapFromFile(const std::string& filename) {
    Data data(getDataFromFile(filename));
    return getValueMapFromData(reinterpret_cast<char*>(data.getBytes()),
                               static_cast<int>(data.getSize()));
}

ValueMap Self::getValueMapFromData(const char* fileData, int fileSize) {
    return getValueFromData(fileData, fileSize).asValueMap();
}

ValueVector Self::getValueVectorFromFile(const std::string& filename) {
    Data data(getDataFromFile(filename));
    return getValueFromData(reinterpret_cast<char*>(data.getBytes()),
                            static_cast<int>(data.getSize()))
        .asValueVector();
}

Value Self::getValueFromData(const char* data, int size) {
    QByteArray array(data, size);
    QBuffer buffer(&array);
    auto variant = PListParser::parsePList(&buffer);
    auto json = QJsonValue::fromVariant(variant);
    return convertToValue(json);
}

bool Self::writeToFile(const ValueMap& dict, const std::string& fullPath) {
    return writeValueMapToFile(dict, fullPath);
}

bool FileUtils::writeValueMapToFile(const ValueMap& dict,
                                    const std::string& fullPath) {
    auto json = convertToJson(cocos2d::Value(dict));
    QVariant variant(json);
    auto plist = PListSerializer::toPList(variant);
    return writeStringToFile(plist.toStdString(), fullPath);
}

bool FileUtils::writeValueVectorToFile(const ValueVector& vecData,
                                       const std::string& fullPath) {
    auto json = convertToJson(cocos2d::Value(vecData));
    QVariant variant(json);
    auto plist = PListSerializer::toPList(variant);
    return writeStringToFile(plist.toStdString(), fullPath);
}
NS_CC_END
