#pragma once
#include "cocos2d.h"
#include "../Math/Vector2.hpp"
#include "../../artemis/Artemis.h"
class SteeringUtils {

public :
	static SteeringUtils* getInstance();

	cocos2d::Vec2 seek(artemis::Entity* e,  cocos2d::Vec2 target);
	cocos2d::Vec2 arrive(artemis::Entity* e, cocos2d::Vec2 target,float slowingRadius);
	cocos2d::Vec2 flee(artemis::Entity* e, cocos2d::Vec2 target);
	cocos2d::Vec2 pursuit(artemis::Entity* e, artemis::Entity* target,const int nextGameStep = 1);
	cocos2d::Vec2 evade(artemis::Entity* e, artemis::Entity* target, const int nextGameStep = 1);

private :
	SteeringUtils();
	~SteeringUtils();
	Vector2* mTemp;

};



