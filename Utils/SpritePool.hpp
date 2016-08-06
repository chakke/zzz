//
//  SpritePool.hpp
//  RacingRushMini
//
//  Created by Manh Tran on 11/3/15.
//
//

#ifndef SpritePool_hpp
#define SpritePool_hpp

#include "cocos2d.h"

class SpritePool : public cocos2d::Ref
{
public:
    static SpritePool* getInstance();
    virtual ~SpritePool();
    
    cocos2d::Sprite* get();
    void push(cocos2d::Sprite* sprite);
    void reserve(long num);
    
CC_CONSTRUCTOR_ACCESS:
    cocos2d::Vector<cocos2d::Sprite*> _sprites;
};

#endif /* SpritePool_hpp */
