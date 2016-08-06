#pragma once
#include "cocos2d.h"
#include "Shape.hpp"
class Circle : public Shape {
public:
	Circle(float x,float y,float radius);
	~Circle();
	bool collide(Shape* otherShape);
	float getRadius();	
	cocos2d::Rect getBoundingBox(const cocos2d::Vec2 &pos = cocos2d::Vec2::ZERO);
protected :
	float radius;
};

