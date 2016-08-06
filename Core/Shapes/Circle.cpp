
#include "Circle.hpp"

Circle::Circle(float x, float y, float radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}

Circle::~Circle()
{
}

bool Circle::collide(Shape * otherShape)
{
	return false;
}

float Circle::getRadius()
{
	return radius;
}

cocos2d::Rect Circle::getBoundingBox(const cocos2d::Vec2 & pos)
{
	return cocos2d::Rect(pos.x +  x-radius,pos.y +  y-radius,2*radius,2*radius);
}

 