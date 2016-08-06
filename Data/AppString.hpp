

#ifndef AppString_hpp
#define AppString_hpp

#include "cocos2d.h"

namespace app_string
{
    extern std::string __LOST__;
    extern std::string __CONNECTED__;
    extern std::string __SUCCESS__;
    extern std::string __FAIL__;
    extern std::string __ERROR_MESSAGE_KEY__;
	extern std::string __LAG_VALUE__;
    extern std::string __CMD_KEY__;
    extern std::string __PARAMS_KEY__;
    extern std::string __UDP__;
    extern std::string __TCP__;
    
    cocos2d::ValueMap* getValueMap(const std::string& file);
};

#endif /* AppString_hpp */
