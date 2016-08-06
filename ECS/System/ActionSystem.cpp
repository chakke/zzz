#include "ActionSystem.h"
#include "../Component/Components.hpp"
#include "../../Config/GameConstants.hpp"
ActionSystem::ActionSystem()
{
	addComponentType<ActionComponent>();
	addComponentType<TypeComponent>();
}

void ActionSystem::initialize()
{
	_delegates.insert(std::make_pair(game::action::DIE_ON_ATTACK,CC_CALLBACK_1(ActionSystem::doActionTroopDie,this)));
	_delegates.insert(std::make_pair(game::action::KILLED_ENEMY, CC_CALLBACK_1(ActionSystem::doActionKilledEnemy, this)));
	_delegates.insert(std::make_pair(game::action::BE_ATTACK, CC_CALLBACK_1(ActionSystem::doActionBeAttack, this)));
}

void ActionSystem::processEntity(artemis::Entity & e)
{
	auto actionComponent = getComponent<ActionComponent>(e);
	if (!actionComponent->isActive()) return;

	auto actions = actionComponent->getActions();
	for (auto action : actions) {
		if (!action.done) {
			if (action.update(world->getDelta())) {				
				if (_delegates.find(action.name) != _delegates.end()) {
					_delegates.at(action.name)(e);
				}
			}
		}		
		if(action.done) actionComponent->removeAction(action.name);
	}
}

void ActionSystem::doActionTroopDie(artemis::Entity &e)
{
	getComponent<VelocityComponent>(e)->getVelocity()->setZero();	
	getComponent<PathFollowComponent>(e)->clear();
	auto animationComponent = getComponent<AnimationComponent>(e);
	animationComponent->animate(animationComponent->getCurrentAnimation() % 2 == 1 ? game::AnimationName::DIE_DOWN : game::AnimationName::DIE_UP);
	auto renderNode = getComponent<RenderComponent>(e)->getView();
	renderNode->setCascadeOpacityEnabled(true);
	renderNode->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(1), cocos2d::FadeOut::create(.5f)));
	
}

void ActionSystem::doActionKilledEnemy(artemis::Entity & e)
{	
	getComponent<PathFollowComponent>(e)->clear();
	auto animationComponent = getComponent<AnimationComponent>(e);
	animationComponent->animate(animationComponent->getCurrentAnimation() %2 ==1 ? game::AnimationName::IDLE_UP : game::AnimationName::IDLE_DOWN);
	getComponent<VelocityComponent>(e)->getVelocity()->setZero();
	// now decide to go some where or attack onother enemy
}


void ActionSystem::doActionBeAttack(artemis::Entity & e)
{
	auto renderNode = getComponent<RenderComponent>(e)->getView();
	if (renderNode) {		
		renderNode->stopActionsByFlags(43234);		
		auto action = cocos2d::Sequence::create(cocos2d::FadeIn::create(.05f), cocos2d::FadeTo::create(.1f,.6f),cocos2d::FadeIn::create(.05f),nullptr);
		action->setFlags(43234);
		renderNode->runAction(action);
	}
}


