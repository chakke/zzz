
#include "AppString.hpp"

namespace app_string
{
    std::string __LOST__ = "lost";
    std::string __CONNECTED__ = "connected";
    std::string __SUCCESS__ = "success";
    std::string __FAIL__ = "fail";
    std::string __ERROR_MESSAGE_KEY__ = "message";
	std::string __LAG_VALUE__ = "lagValue";
    std::string __CMD_KEY__ = "cmd";
    std::string __PARAMS_KEY__ = "params";
    std::string __UDP__ = "udp";
    std::string __TCP__ = "tcp";
	
    
    std::unordered_map<std::string, cocos2d::ValueMap*> __value_maps__;
    
    cocos2d::ValueMap* getValueMap(const std::string& file)
    {
        if (__value_maps__.find(file) == __value_maps__.end())
        {
            cocos2d::ValueMap* map = new cocos2d::ValueMap();
            *map = cocos2d::FileUtils::getInstance()->getValueMapFromFile(file);
            __value_maps__.insert(std::make_pair(file, map));
        }
        
        return __value_maps__.at(file);
    }
};