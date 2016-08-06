#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Core/Math/Vector2.hpp"
class PositionComponent : public artemis::Component {

public:
	PositionComponent(float x,float y);
	~PositionComponent();
	/*
	use this function instead of setting in the position itself.
	*/
	void setPosition(float x, float y);
	void setPosition(const cocos2d::Vec2 &pos);
	void setPosition(Vector2* pos);

	Vector2* getPosition();
	Vector2* getLastPosition();
protected:
	Vector2* mPosition;
	Vector2* mLastPosition;
};
