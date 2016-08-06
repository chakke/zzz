#include "TroopSystem.h"
#include "../../ECS/Component/Components.hpp"
#include "../../Config/GameConstants.hpp"
TroopSystem::TroopSystem()
{
	addComponentType<StateComponent>();
	addComponentType<TypeComponent>();
	addComponentType<AnimationComponent>();
	addComponentType<VelocityComponent>();
}

void TroopSystem::processEntity(artemis::Entity & e)
{
	auto state = getComponent<StateComponent>(e);
	switch (state->getStateName())
	{
	case game::state::TROOP_STAY:
		doTroopStateStay(e);
		break;
	case game::state::TROOP_MOVE:
		doTroopStateMove(e);
		break;
	case game::state::TROOP_ATTACK:
		doTroopStateAttack(e);
		break;
	}
}

void TroopSystem::doTroopStateStay(artemis::Entity & e)
{
	if (getComponent<VelocityComponent>(e)->getVelocity()->isZero()) {
		auto animationComponent = getComponent<AnimationComponent>(e);
		animationComponent->animate(animationComponent->getCurrentAnimation() % 2 == 1 ? game::AnimationName::IDLE_UP : game::AnimationName::IDLE_DOWN);
	}
}

void TroopSystem::doTroopStateMove(artemis::Entity & e)
{
	auto animationComponent = getComponent<AnimationComponent>(e);
	auto velocity = getComponent<VelocityComponent>(e)->getVelocity();

	if (velocity->isZero()) {		
		animationComponent->animate(animationComponent->getCurrentAnimation() % 2 == 1 ? game::AnimationName::IDLE_UP : game::AnimationName::IDLE_DOWN);
	}
	else {
		float moveUp = velocity->getY() > 0;
		bool flip = velocity->getX() < 0;
		animationComponent->animate(moveUp ? game::AnimationName::MOVE_UP : game::AnimationName::MOVE_DOWN);
		animationComponent->setFlip(flip);
	}
	
	auto pathFollowComponent = getComponent<PathFollowComponent>(e);
	if (!pathFollowComponent->hasNextPoint()) {
		auto targetComponent = getComponent<TargetComponent>(e);
		if (targetComponent && targetComponent->hasTarget()) {
			getComponent<StateComponent>(e)->setState(game::state::TROOP_ATTACK);
		}
		else {
			getComponent<StateComponent>(e)->setState(game::state::TROOP_STAY);
		}		
	}
}

void TroopSystem::doTroopStateAttack(artemis::Entity & e)
{
	
}
