#include "Box.hpp"

Box::Box(float x, float y, float width, float height) : x(x),y(y),width(width),height(height)
{	
}

Box::~Box()
{
}

bool Box::collide(Shape * otherShape)
{
	return false;
}

void Box::setWidth(float width)
{
	this->width = width;
}

void Box::setHeight(float height)
{
	this->height = height;
}

float Box::getWidth()
{
	return width;
}

float Box::getHeight()
{
	return height;
}

float Box::getX()
{
	return x;
}

float Box::getY()
{
	return y;
}

cocos2d::Vec2 Box::getPosition(game::Align alignment)
{
	cocos2d::Vec2 result(x,y);

	switch (alignment)
	{
	case game::Align::BOTTOM:
		result.y -= height / 2;
		break;
	case game::Align::BOTTOM_LEFT:
		result.x -= width / 2;
		result.y -= height / 2;
		break;
	case game::Align::LEFT:
		result.x -= width / 2;		
		break;
	case game::Align::TOP_LEFT:
		result.x -= width / 2;
		result.y += height / 2;
		break;
	case game::Align::TOP:		
		result.y += height / 2;
		break;
	case game::Align::TOP_RIGHT:
		result.x += width / 2;
		result.y += height / 2;
		break;
	case game::Align::RIGHT:
		result.x += width / 2;		
		break;
	case game::Align::BOTTOM_RIGHT:
		result.x += width / 2;
		result.y -= height / 2;
		break;
	default:
		result.x = x;
		result.y = y;
		break;
	}	
	return result;
}

void Box::setPosition(cocos2d::Vec2 position)
{
	this->x = position.x;
	this->y = position.y;
}

void Box::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}


cocos2d::Rect Box::getBoundingBox(const cocos2d::Vec2 & pos)
{
	return cocos2d::Rect(pos.x + x- width/2,pos.y +  y - height/2, width, height);
}
