#pragma once
#include "../../artemis/Artemis.h"
#include "cocos2d.h"
class ActionSystem : public artemis::EntityProcessingSystem
{
public:
	ActionSystem();
	void initialize();
	virtual void processEntity(artemis::Entity &e);		

private :
	void doActionTroopDie(artemis::Entity & e);
	void doActionKilledEnemy(artemis::Entity & e);
	void doActionBeAttack(artemis::Entity & e);
	std::unordered_map<int, std::function<void(artemis::Entity&)>> _delegates;
};

