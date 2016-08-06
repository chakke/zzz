#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class HealthComponent : public artemis::Component {

public:
	HealthComponent(float health = 5);
	~HealthComponent();
	bool beDamage(float damage);
	void setHealth(float health,bool fullHealth = false);
	void setFullHealth(float health);
	float getHealth();
	float getFullHealth();
	int getNumberOfAttacker();
	std::vector<int> getAttackers();
	void addAttacker(int id);
	void removeAllAttacker();
	void removeAttacker(int id);
	bool hasAttacker();
protected:
	float mFullHealth;
	float mHealth;
	std::vector<int> _attackers;
	
};
