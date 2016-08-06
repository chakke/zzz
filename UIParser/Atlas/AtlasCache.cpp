//
//  AtlasCache.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#include "AtlasCache.hpp"
#include "AdvanceSpriteFrameCache.h"

namespace atlas_cache
{
    cocos2d::Map<std::string, AdvanceSpriteFrameCache*> __holder;
    
    void reserve(const std::string& atlasPath)
    {
        if (!__holder.at(atlasPath))
        {
            auto cache = new AdvanceSpriteFrameCache();
            cache->addSpriteFramesWithFile(atlasPath);
            __holder.insert(atlasPath, cache);
            cache->autorelease();
        }
    }
    
    cocos2d::SpriteFrame* getSpriteFrame(const std::string& atlasPath, const std::string& frame)
    {
        reserve(atlasPath);
		auto f  = __holder.at(atlasPath)->getSpriteFrameByName(frame);
		if (!f) {
			std::string prepath = atlasPath.c_str();
			prepath.erase(prepath.end() - 6, prepath.end());
			for (int i = 0; i < 5; i++) {
				std::string atlasFile = cocos2d::StringUtils::format("%s%d.plist", prepath.c_str(), i).c_str();
				reserve(atlasFile);
				auto fs = __holder.at(atlasFile)->getSpriteFrameByName(frame);
				if (fs)  return fs;
			}
			CCLOG("Frame %s not found in atlas %s", frame.c_str(), atlasPath.c_str());
		}	
		return f;
    }
};