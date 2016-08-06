#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/AttackComponent.hpp"

class AttackSystem : public artemis::EntityProcessingSystem
{
public:
	AttackSystem();	
	virtual void processEntity(artemis::Entity &e);	
	virtual void lookForTarget(artemis::Entity &e);	
	void doAttack(artemis::Entity &attacker, artemis::Entity &victim);
};

