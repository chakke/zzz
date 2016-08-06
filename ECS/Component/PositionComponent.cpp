#include "PositionComponent.hpp"

PositionComponent::PositionComponent(float x, float y)
{	
	mPosition = new Vector2(x,y);
	mLastPosition = new Vector2(x, y);
	setActive(true);
}

PositionComponent::~PositionComponent()
{
}

void PositionComponent::setPosition(float x, float y)
{
	mLastPosition->set(mPosition);
	mPosition->set(x,y);
}

void PositionComponent::setPosition(const cocos2d::Vec2 & pos)
{
	setPosition(pos.x,pos.y);
}

void PositionComponent::setPosition(Vector2 * pos)
{
	setPosition(pos->getX(),pos->getY());
}

Vector2 * PositionComponent::getPosition()
{
	return mPosition;
}

Vector2 * PositionComponent::getLastPosition()
{
	return mLastPosition;
}
