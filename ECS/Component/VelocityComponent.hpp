#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Core/Math/Vector2.hpp"
class VelocityComponent : public artemis::Component {

public:
	VelocityComponent(float x,float y);
	~VelocityComponent();
	/*
	use this function instead of setting in the position itself.
	*/
	float getMaxForce();
	void setMaxForce(float max_force);
	
	void setMaxVelocity(float max_speed);
	float getMaxVelocity();
	Vector2* getVelocity();
protected:
	Vector2* mVelocity;	
	float MAX_SPEED;
	float MAX_FORCE;	
};
