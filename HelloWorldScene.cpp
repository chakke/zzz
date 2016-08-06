#include "HelloWorldScene.h"
#include <spine/spine-cocos2dx.h>
USING_NS_CC;

Scene* HelloWorld::createScene()
{

    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch* touch, Event* event) {
/*
		auto pos = convertToNodeSpace(touch->getLocation());

		auto skeleton = spine::SkeletonAnimation::createWithFile("spine/bobinh.json","spine/bobinh.atlas",1.0f);		
		skeleton->setAnimation(0,"f-idle",true);
		skeleton->setSkin("1");
		skeleton->setScale(.2f);
		skeleton->setAnchorPoint(cocos2d::Vec2(.5f,.1f));		
		skeleton->setPosition(pos);
		addChild(skeleton);

		CCLOG("Number of skeleton %d", index++);*/
		return true;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event) {

		auto pos = convertToNodeSpace(touch->getLocation());

		auto skeleton = spine::SkeletonAnimation::createWithFile("spine/bobinh.json", "spine/bobinh.atlas", 1.0f);
		skeleton->setAnimation(0, "f-attack", true);
		skeleton->setSkin("1");
		skeleton->setScale(.2f);
		skeleton->setAnchorPoint(cocos2d::Vec2(.5f, .1f));
		skeleton->setPosition(pos);
		addChild(skeleton);
		

	};

	_eventDispatcher->addEventListenerWithFixedPriority(listener,1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
