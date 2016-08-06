#include "Preferences.h"

Preferences* Preferences::create(const std::string& file, bool fullPath, bool autoreleased)
{
    std::string fullfile = fullPath ? file : cocos2d::FileUtils::getInstance()->fullPathFromRelativeFile(file, cocos2d::FileUtils::getInstance()->getWritablePath());
    auto pre = new Preferences(fullfile);
    if(autoreleased) pre->autorelease();
    return pre;
}

Preferences::Preferences(const std::string& file)
{
    map = cocos2d::FileUtils::getInstance()->getValueMapFromFile(file);
    this->file = file;
}

Preferences::~Preferences()
{
    map.clear();
}

bool Preferences::getBool(const std::string& key, bool defValue)
{
    if (map.find(key) != map.end())
    {
        return map[key].asBool();
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(defValue)));
        return defValue;
    }
}

int  Preferences::getInt(const std::string& key, int defValue)
{
    if (map.find(key) != map.end())
    {
        return map[key].asInt();
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(defValue)));
        return defValue;
    }
}

std::string Preferences::getString(const std::string& key, std::string defValue)
{
    if (map.find(key) != map.end())
    {
        return map[key].asString();
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(defValue)));
        return defValue;
    }
}

void Preferences::putInt(const std::string& key, int value)
{
    if (map.find(key) != map.end())
    {
        map[key] = value;
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(value)));
    }
}

void Preferences::putBool(const std::string& key, bool value)
{
    if (map.find(key) != map.end())
    {
        map[key] = value;
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(value)));
    }
}

void Preferences::putString(const std::string& key, const std::string& value)
{
    if (map.find(key) != map.end())
    {
        map[key] = value;
    }
    else
    {
        map.insert(std::map<std::string, cocos2d::Value>::value_type(key, cocos2d::Value(value)));
    }
}

void Preferences::flush()
{
    cocos2d::FileUtils::getInstance()->writeToFile(map, file);
}