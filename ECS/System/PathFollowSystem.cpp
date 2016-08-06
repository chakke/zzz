#include "PathFollowSystem.h"
#include "../../Core/SteeringBehaviors/SteeringUtils.hpp"
PathFollowSystem::PathFollowSystem()
{	
	addComponentType<VelocityComponent>();
	addComponentType<PositionComponent>();
	addComponentType<PathFollowComponent>();

	mTemp = new Vector2();	
}
PathFollowSystem::~PathFollowSystem() {
	CC_SAFE_RELEASE_NULL(mTemp);	
}

void PathFollowSystem::initialize()
{	
	positionMapper.init(*world);
	velocityMapper.init(*world);
	pathFollowMapper.init(*world);	
}

void PathFollowSystem::processEntity(artemis::Entity & e)
{
	auto pathFollow = pathFollowMapper.get(e);
	if (!pathFollow->isActive()) return;
	if (!pathFollow->hasNextPoint()) return;
	auto target = pathFollow->peek();
	mTemp->set(SteeringUtils::getInstance()->arrive(&e,target.mPosition,target.mEpsilon));
	velocityMapper.get(e)->getVelocity()->add(mTemp);
	float dst = mTemp->set(target.mPosition)->dst(positionMapper.get(e)->getPosition());
	if (dst < target.mEpsilon) {
		pathFollow->pop();
	}
}
