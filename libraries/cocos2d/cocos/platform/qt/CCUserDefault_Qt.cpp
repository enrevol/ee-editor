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
    return defaultValue;
}

int Self::getIntegerForKey(const char* key) {
    return getIntegerForKey(key, 0);
}

int Self::getIntegerForKey(const char* key, int defaultValue) {
    return defaultValue;
}

float Self::getFloatForKey(const char* key) {
    return getFloatForKey(key, 0);
}

float Self::getFloatForKey(const char* key, float defaultValue) {
    return defaultValue;
}

double Self::getDoubleForKey(const char* key) {
    return getDoubleForKey(key, 0);
}

double Self::getDoubleForKey(const char* key, double defaultValue) {
    return defaultValue;
}

std::string Self::getStringForKey(const char* key) {
    return getStringForKey(key, "");
}

std::string Self::getStringForKey(const char* key,
                                  const std::string& defaultValue) {
    return defaultValue;
}

Data Self::getDataForKey(const char* key) {
    return getDataForKey(key, Data::Null);
}

Data Self::getDataForKey(const char* key, const Data& defaultValue) {
    return Data::Null;
}

void Self::setBoolForKey(const char* key, bool value) {}

void Self::setIntegerForKey(const char* key, int value) {}

void Self::setFloatForKey(const char* key, float value) {}

void Self::setDoubleForKey(const char* key, double value) {}

void Self::setStringForKey(const char* key, const std::string& value) {}

void Self::setDataForKey(const char* key, const Data& value) {
    //
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
    //
}
NS_CC_END
