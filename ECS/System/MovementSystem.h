#pragma once
#include "../../artemis/Artemis.h"
#include "../../Core/Math/Vector2.hpp"

class MovementSystem : public artemis::EntityProcessingSystem
{
public:
	MovementSystem();
	~MovementSystem();	
	virtual void processEntity(artemis::Entity &e);	
protected:	
	Vector2* mTemp;
};

