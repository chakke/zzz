#pragma once
#include "../../artemis/Artemis.h"
#include "../../Core/Math/Vector2.hpp"
class AfterPhysicSystem : public artemis::EntityProcessingSystem
{
public:
	AfterPhysicSystem();
	~AfterPhysicSystem();
	virtual void initialize();
	virtual void begin();
	virtual void processEntity(artemis::Entity &e);
	virtual void end();
protected:	
	Vector2* mTemp;
};

