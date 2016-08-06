//
//  MediaCache.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#ifndef MediaCache_hpp
#define MediaCache_hpp

#include "cocos2d.h"

namespace media_cache
{
    void reserveSound(const std::string& filePath);
    
    void playSound(const std::string& filePath, bool loop = false, float volume = 1);
    
    void reserveMusic(const std::string& filePath);
    
    void playMusic(const std::string& filePath, bool loop = true);
    
};

#endif /* MediaCache_hpp */
