#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/RemoveableComponent.hpp"
#include "../Component/RenderComponent.hpp"

class RemoveEntitySystem : public artemis::EntityProcessingSystem
{
public:
	RemoveEntitySystem();
	virtual void initialize();
	virtual void begin();
	virtual void processEntity(artemis::Entity &e);
	virtual void end();

protected:
	artemis::ComponentMapper<RemoveableComponent> removeMapper;
	artemis::ComponentMapper<RenderComponent> renderMapper;
};

