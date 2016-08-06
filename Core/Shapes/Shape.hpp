#pragma once
#include "cocos2d.h"
#include "../Enums.hpp"
class Shape {
public:
	Shape();
	~Shape();	
	virtual bool collide(Shape* otherShape) = 0;
	virtual void setPosition(float x, float y,const game::Align align = game::Align::CENTER);
	virtual void setPositionX(float x,const game::Align align = game::Align::CENTER);
	virtual void setPositionY(float y,const game::Align align = game::Align::CENTER);
	virtual float getPositionX(const game::Align align = game::Align::CENTER);
	virtual float getPositionY(const game::Align align = game::Align::CENTER);
	virtual cocos2d::Rect getBoundingBox(const cocos2d::Vec2 &pos = cocos2d::Vec2::ZERO) = 0;
protected :
	float x;
	float y;	
};

