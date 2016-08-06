#pragma once
#include "cocos2d.h"
#include "Shape.hpp"

/* x, y is the center of this shape*/
class Box : public Shape {
public:
	Box(float x,float y,float width,float height);
	~Box();
	bool collide(Shape* otherShape);
	
	void setWidth(float width);
	void setHeight(float height);

	float getWidth();
	float getHeight();
	float getX();
	float getY();

	cocos2d::Vec2 getPosition(game::Align alignment);
	void setPosition(cocos2d::Vec2 position);
	void setPosition(float x,float y);
	cocos2d::Rect getBoundingBox(const cocos2d::Vec2 &pos = cocos2d::Vec2::ZERO);
protected:


	float x;
	float y;
	float width;
	float height;
	

};

