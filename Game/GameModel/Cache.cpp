//
//  Cache.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/20/16.
//
//

#include "Cache.hpp"
#include "../../Utils/Preferences.h"

namespace game_model
{
    Preferences* __user_cache_pref__ = nullptr;
    
    void load_user_cache()
    {
        __user_cache_pref__ = Preferences::create("usercache", false, false);
        __user_cache__ = new User();
        __user_cache__->_name = __user_cache_pref__->getString("name", "");
        __user_cache__->_account = __user_cache_pref__->getString("account", "");
        __user_cache__->_password = __user_cache_pref__->getString("password", "");
        __user_cache__->_type    = __user_cache_pref__->getInt("type", -1);
		__user_cache__->_remember_password = __user_cache_pref__->getBool("rememberpass", true);
    }
    
    void save_user_cache()
    {
        __user_cache_pref__->putString("name", __user_cache__->_name);
        __user_cache_pref__->putString("account", __user_cache__->_account);
        __user_cache_pref__->putString("password", __user_cache__->_password);
        __user_cache_pref__->putInt("type", __user_cache__->_type);
		__user_cache_pref__->putBool("rememberpass", __user_cache__->_remember_password);
        __user_cache_pref__->flush();
    }
    
    User* __user_cache__ = nullptr;
};