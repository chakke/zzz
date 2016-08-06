#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/BuilderComponent.hpp"
#include "../Component/PlaySideComponent.hpp"
#include "../Component/IDComponent.hpp"

class BuildSystem : public artemis::EntityProcessingSystem
{
public:
	BuildSystem();
	virtual void initialize();	
	virtual void processEntity(artemis::Entity &e);	
protected:
	artemis::ComponentMapper<PlaySideComponent> playSideMapper;
	artemis::ComponentMapper<BuilderComponent> builderMapper;
	artemis::ComponentMapper<IDComponent> idMapper;
};

