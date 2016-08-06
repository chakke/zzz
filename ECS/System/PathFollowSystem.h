#pragma once
#include "../../artemis/Artemis.h"
#include "../../ECS/Component/PositionComponent.hpp"
#include "../../ECS/Component/VelocityComponent.hpp"
#include "../../ECS/Component/PathFollowComponent.hpp"
#include "../../Core/Math/Vector2.hpp"


class PathFollowSystem : public artemis::EntityProcessingSystem
{
public:
	PathFollowSystem();
	~PathFollowSystem();
	virtual void initialize();
	virtual void processEntity(artemis::Entity &e);

protected:

	artemis::ComponentMapper<PositionComponent> positionMapper;
	artemis::ComponentMapper<VelocityComponent> velocityMapper;
	artemis::ComponentMapper<PathFollowComponent> pathFollowMapper;	
	
private :
	Vector2* mTemp;	
};

