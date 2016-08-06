#include "EffectSystem.h"
#include "../Component/Components.hpp"
#include <spine/spine-cocos2dx.h>
EffectSystem::EffectSystem()
{

}

void EffectSystem::process()
{
	
}

void EffectSystem::showEffectAttack(std::shared_ptr<connection_object> data)
{
	
	int castleID = data->getInt("castle_id");
	auto castle = &world->getTagManager()->getEntity(cocos2d::StringUtils::format("castle_%d", castleID));
	auto effect = &world->getTagManager()->getEntity("attack_effect_entity");
	auto pos = getComponent<PositionComponent>(*castle)->getPosition();
	getComponent<PositionComponent>(*effect)->setPosition(pos);
	auto node = getComponent<RenderComponent>(*effect);	
	{
		auto skeleton = spine::SkeletonAnimation::createWithFile("spine/sword2.json", "spine/sword2.atlas");
		skeleton->addAnimation(0, "sword_fight", false);
		skeleton->setLocalZOrder(100);
		skeleton->setPosition(cocos2d::Vec2(0, 20));
		skeleton->setScale(1.4f);
		skeleton->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.2f), cocos2d::FadeOut::create(.8f), cocos2d::RemoveSelf::create(), nullptr));		
		node->getView()->addChild(skeleton); }
}

void EffectSystem::showEffectShield(std::shared_ptr<connection_object> data)
{
	int castleID = data->getInt("castle_id");
	auto castle = &world->getTagManager()->getEntity(cocos2d::StringUtils::format("castle_%d", castleID));
	auto effect = &world->getTagManager()->getEntity("safe_effect_entity");
	auto pos = getComponent<PositionComponent>(*castle)->getPosition();	
	getComponent<PositionComponent>(*effect)->setPosition(pos);		
	auto node = getComponent<RenderComponent>(*effect);
	node->getView()->stopAllActions();
	node->getView()->setOpacity(255);
	node->getView()->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.4f), cocos2d::FadeOut::create(1), nullptr));
}
