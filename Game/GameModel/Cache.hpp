//
//  Cache.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/20/16.
//
//

#ifndef Cache_hpp
#define Cache_hpp

#include "User.hpp"

namespace game_model
{
    void load_user_cache();
    
    void save_user_cache();
    
    extern User* __user_cache__;
};

#endif /* Cache_hpp */
