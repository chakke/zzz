#include "RemoveEntitySystem.h"

RemoveEntitySystem::RemoveEntitySystem()
{
	addComponentType<RemoveableComponent>();
	addComponentType<RenderComponent>();	
}
void RemoveEntitySystem::initialize(){
	removeMapper.init(*world);
	renderMapper.init(*world);	
}

void RemoveEntitySystem::begin(){}

void RemoveEntitySystem::processEntity(artemis::Entity &e){
	RemoveableComponent* remove = removeMapper.get(e);
	RenderComponent* render = renderMapper.get(e);
	if (!remove->isActive()) return;
	if (remove->getRemainTime() <= 0) {
		render->getView()->removeFromParent();
		world->deleteEntity(e);
	}
	else {
		remove->setRemainTime(remove->getRemainTime() - world->getDelta());
	}
}
void RemoveEntitySystem::end(){}

