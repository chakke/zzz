#pragma once
#include "../../artemis/Artemis.h"
#include "../../ECS/Component/PositionComponent.hpp"
#include "../../ECS/Component/VelocityComponent.hpp"
#include "../../ECS/Component/RenderComponent.hpp"

#include "../../Core/Math/Vector2.hpp"


class VelocityDrawSystem : public artemis::EntityProcessingSystem
{
public:
	VelocityDrawSystem();
	virtual void initialize();
	virtual void begin();
	virtual void processEntity(artemis::Entity &e);
protected:
	artemis::ComponentMapper<PositionComponent> positionMapper;
	artemis::ComponentMapper<VelocityComponent> velocityMapper;
	artemis::ComponentMapper<RenderComponent> renderMapper;
	
	Vector2* mTemp;
};

