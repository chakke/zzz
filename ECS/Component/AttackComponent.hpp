#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class AttackComponent : public artemis::Component {

public:
	AttackComponent(float damage = 1);
	~AttackComponent();
	void setDamage(float damage);
	float getDamage();
	bool update(float dt);
	void setTime(float t);	
	void setTimePerAttack(float t);
protected:	
	float mDamage;
	float timeAttack;
	float time;
};
