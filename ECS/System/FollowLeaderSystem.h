#pragma once
#include "../../artemis/Artemis.h"
#include "../../Core/Math/Vector2.hpp"


class FollowLeaderSystem : public artemis::EntityProcessingSystem
{
public:
	FollowLeaderSystem();
	~FollowLeaderSystem();	
	virtual void processEntity(artemis::Entity &e);

private :
	Vector2* mTemp;	
};

