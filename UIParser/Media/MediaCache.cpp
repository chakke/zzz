//
//  MediaCache.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#include "MediaCache.hpp"
#include "SimpleAudioEngine.h"

namespace media_cache
{
    std::unordered_map<std::string, bool> __soundHolder;
    std::unordered_map<std::string, bool> __musicHolder;
    
    void reserveSound(const std::string& filePath)
    {
        if (__soundHolder.find(filePath) == __soundHolder.end()
            || !__soundHolder[filePath])
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(filePath.c_str());
            __soundHolder.insert(std::make_pair(filePath, true));
        }
    }
    
    void playSound(const std::string& filePath, bool loop, float volume)
    {
        reserveSound(filePath);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(), loop, 1.0F, 0.0F, volume);
    }
    
    void reserveMusic(const std::string& filePath)
    {
        if (__musicHolder.find(filePath) == __musicHolder.end()
            || !__musicHolder[filePath])
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath.c_str());
            __musicHolder.insert(std::make_pair(filePath, true));
        }
    }

    void playMusic(const std::string& filePath, bool loop)
    {
        reserveMusic(filePath);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath.c_str(), loop);
    }
};