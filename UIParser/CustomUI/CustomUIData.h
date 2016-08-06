//
//  CustomUIData.h
//  GameBai69
//
//  Created by Manh Tran on 2/19/16.
//
//

#ifndef CustomUIData_h
#define CustomUIData_h

#include "cocos2d.h"

class CustomUIData
{
public:
    
    CustomUIData()
    {
        _attributes = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::string>>>(new std::unordered_map<std::string, std::shared_ptr<std::string>>());
    }
    
    virtual ~CustomUIData()
    {
        _custom_ui_data.clear();
    }
    
    void addCustomUIData(cocos2d::Ref* data)
    {
        if (!_custom_ui_data.contains(data))
        {
            _custom_ui_data.pushBack(data);
        }
    }
    
    const cocos2d::Vector<cocos2d::Ref*>& getCustomUIData()
    {
        return _custom_ui_data;
    }
    
    void setCustomAttribute(const std::string& key, const std::string& value)
    {
        _attributes->insert(std::make_pair(key, std::shared_ptr<std::string>(new std::string(value))));
    }
    
    void setCustomAttribute(const std::string& key, const std::shared_ptr<std::string> value)
    {
        _attributes->insert(std::make_pair(key, std::shared_ptr<std::string>(value)));
    }
    
    bool hasCustomAttribute(const std::string& key)
    {
        return _attributes->find(key) != _attributes->end();
    }
    
    std::shared_ptr<std::string> getCustomAttribute(const std::string& key)
    {
        return _attributes->at(key);
    }
    
protected:
    cocos2d::Vector<cocos2d::Ref*> _custom_ui_data;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::string>>> _attributes;
};

#endif /* CustomUIData_h */
