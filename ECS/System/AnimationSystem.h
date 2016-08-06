#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/RenderComponent.hpp"
#include "../Component/AnimationComponent.hpp"
#include "../Component/PlaySideComponent.hpp"
#include "../Component/TypeComponent.hpp"

class AnimationSystem : public artemis::EntityProcessingSystem
{
public:
	AnimationSystem();	
	virtual void processEntity(artemis::Entity &e);
	
protected:	
};

