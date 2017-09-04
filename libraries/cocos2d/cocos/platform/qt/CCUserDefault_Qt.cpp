#include "platform/qt/CCUserDefault_Qt.hpp"

NS_CC_BEGIN
using Self = UserDefault;

Self* Self::_userDefault = nullptr;
std::string Self::_filePath;

Self::UserDefault() {}

Self::~UserDefault() {}

bool Self::getBoolForKey(const char* key) {
    return getBoolForKey(key, false);
}

bool Self::getBoolForKey(const char* key, bool defaultValue) {
    Q_UNUSED(key);
    return defaultValue;
}

int Self::getIntegerForKey(const char* key) {
    return getIntegerForKey(key, 0);
}

int Self::getIntegerForKey(const char* key, int defaultValue) {
    Q_UNUSED(key);
    return defaultValue;
}

float Self::getFloatForKey(const char* key) {
    return getFloatForKey(key, 0);
}

float Self::getFloatForKey(const char* key, float defaultValue) {
    Q_UNUSED(key);
    return defaultValue;
}

double Self::getDoubleForKey(const char* key) {
    return getDoubleForKey(key, 0);
}

double Self::getDoubleForKey(const char* key, double defaultValue) {
    Q_UNUSED(key);
    return defaultValue;
}

std::string Self::getStringForKey(const char* key) {
    return getStringForKey(key, "");
}

std::string Self::getStringForKey(const char* key,
                                  const std::string& defaultValue) {
    Q_UNUSED(key);
    return defaultValue;
}

Data Self::getDataForKey(const char* key) {
    return getDataForKey(key, Data::Null);
}

Data Self::getDataForKey(const char* key, const Data& defaultValue) {
    Q_UNUSED(key);
    return Data::Null;
}

void Self::setBoolForKey(const char* key, bool value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

void Self::setIntegerForKey(const char* key, int value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

void Self::setFloatForKey(const char* key, float value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

void Self::setDoubleForKey(const char* key, double value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

void Self::setStringForKey(const char* key, const std::string& value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

void Self::setDataForKey(const char* key, const Data& value) {
    Q_UNUSED(key);
    Q_UNUSED(value);
}

Self* Self::getInstance() {
    if (_userDefault == nullptr) {
        _userDefault = new Self();
    }
    return _userDefault;
}

void Self::destroyInstance() {
    CC_SAFE_DELETE(_userDefault);
}

Self* Self::sharedUserDefault() {
    return getInstance();
}

void Self::purgeSharedUserDefault() {
    return destroyInstance();
}

void Self::initXMLFilePath() {}

bool Self::createXMLFile() {
    return false;
}

const std::string& Self::getXMLFilePath() {
    return _filePath;
}

void Self::flush() {}

void Self::deleteValueForKey(const char* key) {
    Q_UNUSED(key);
}
NS_CC_END
