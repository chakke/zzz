//
//  AtlasCache.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#ifndef AtlasCache_hpp
#define AtlasCache_hpp

#include "cocos2d.h"

namespace atlas_cache
{
    cocos2d::SpriteFrame* getSpriteFrame(const std::string& atlasPath, const std::string& frame);
    
    void reserve(const std::string& atlasPath);
};

#endif /* AtlasCache_hpp */
