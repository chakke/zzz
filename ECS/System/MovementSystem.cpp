#include "MovementSystem.h"
#include "../Component/Components.hpp"
#include "../Component/VelocityComponent.hpp"
#include "../../Core/SteeringBehaviors/SteeringUtils.hpp"

MovementSystem::MovementSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<VelocityComponent>();
	addComponentType<PathFollowComponent>();

	mTemp = new Vector2();
}
MovementSystem::~MovementSystem() {
	CC_SAFE_RELEASE_NULL(mTemp);
}


void MovementSystem::processEntity(artemis::Entity & e)
{
	auto velocity = getComponent<VelocityComponent>(e);
	auto position = getComponent<PositionComponent>(e);
	auto pathFollowComponent = getComponent<PathFollowComponent>(e);
	if (!position->isActive()) return;
	if (pathFollowComponent->hasNextPoint()) {
		if (position->getPosition()->dst(pathFollowComponent->target().mPosition) < pathFollowComponent->target().mEpsilon) {
			velocity->getVelocity()->setZero();
			pathFollowComponent->clear();
		}
		else {
			mTemp->set(SteeringUtils::getInstance()->seek(&e, pathFollowComponent->target().mPosition));
			velocity->getVelocity()->add(mTemp)->limit(velocity->getMaxVelocity());
		}
	}
}
