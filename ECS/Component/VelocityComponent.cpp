#include "VelocityComponent.hpp"

VelocityComponent::VelocityComponent(float x, float y)
{
	mVelocity = new Vector2(x,y);		
	setMaxVelocity(3);
	setMaxForce(2.4f);
}

VelocityComponent::~VelocityComponent(){}

float VelocityComponent::getMaxForce()
{
	return MAX_FORCE;
}

void VelocityComponent::setMaxForce(float max_force)
{
	this->MAX_FORCE = max_force;
}

void VelocityComponent::setMaxVelocity(float max_speed)
{
	MAX_SPEED = max_speed;
}


float VelocityComponent::getMaxVelocity()
{
	return MAX_SPEED;
}

Vector2 * VelocityComponent::getVelocity()
{
	return mVelocity;
}
