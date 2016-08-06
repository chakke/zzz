#pragma once
#include "cocos2d.h"

class Preferences : public cocos2d::Ref
{
public:
    static Preferences* create(const std::string& file, bool fullPath, bool autoreleased);
    virtual ~Preferences();
    
    bool getBool(const std::string& key, bool defValue);
    int  getInt(const std::string& key, int defValue);
    std::string getString(const std::string& key, std::string defValue);
    
    void putInt(const std::string& key, int value);
    void putBool(const std::string& key, bool value);
    void putString(const std::string& key, const std::string& value);
    
    void flush();
    
    cocos2d::ValueMap* getMap() { return &map; }
private:
    Preferences(const std::string& file);
    cocos2d::ValueMap map;
    std::string file;
};