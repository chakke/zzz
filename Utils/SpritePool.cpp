//
//  SpritePool.cpp
//  RacingRushMini
//
//  Created by Manh Tran on 11/3/15.
//
//

#include "SpritePool.hpp"

USING_NS_CC;

static SpritePool* _instance = nullptr;

SpritePool* SpritePool::getInstance()
{
    if (!_instance) {
        _instance = new SpritePool();
    }
    return _instance;
}

SpritePool::~SpritePool()
{
    _sprites.clear();
}

void SpritePool::reserve(long num)
{
    while (_sprites.size() < num) {
        _sprites.pushBack(Sprite::create());
    }
}

cocos2d::Sprite* SpritePool::get()
{
    reserve(1);
    auto sprite = _sprites.back();
    if ( ! PoolManager::getInstance()->getCurrentPool()->contains(sprite))
    {
        sprite->retain();
        sprite->autorelease();
    }
    _sprites.popBack();
    
    sprite->unscheduleAllCallbacks();
    sprite->setColor(Color3B::WHITE);
    sprite->setRotation3D(Vec3(0,0,0));
    sprite->setScale(1);
    sprite->setOpacity(255);
    sprite->setVisible(true);
    sprite->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    
    return sprite;
}

void SpritePool::push(cocos2d::Sprite* sprite)
{
    _sprites.pushBack(sprite);
}