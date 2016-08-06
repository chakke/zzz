#include "AfterPhysicSystem.h"
#include "../Component/PositionComponent.hpp"
#include "../Component/VelocityComponent.hpp"
AfterPhysicSystem::AfterPhysicSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<VelocityComponent>();	
	mTemp = new Vector2();
}
AfterPhysicSystem::~AfterPhysicSystem() {
	CC_SAFE_RELEASE_NULL(mTemp);
}

void AfterPhysicSystem::initialize(){}

void AfterPhysicSystem::begin(){}

void AfterPhysicSystem::processEntity(artemis::Entity & e)
{
	auto velocity = getComponent<VelocityComponent>(e);
	auto position = getComponent<PositionComponent>(e);
	if (!position->isActive()) return;
	if (velocity->getVelocity()->isZero()) return;
	{
		velocity->getVelocity()->limit(velocity->getMaxVelocity());		
		mTemp->set(velocity->getVelocity())->scl(world->getDelta());
		position->getPosition()->add(mTemp);		
	}
}

void AfterPhysicSystem::end()
{
}
