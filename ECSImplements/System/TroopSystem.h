#pragma once
#include "../../artemis/Artemis.h"



class TroopSystem : public artemis::EntityProcessingSystem
{
public:
	TroopSystem();
	virtual void processEntity(artemis::Entity &e);
protected:
	void doTroopStateStay(artemis::Entity &e);
	void doTroopStateMove(artemis::Entity &e);
	void doTroopStateAttack(artemis::Entity &e);
	
};

