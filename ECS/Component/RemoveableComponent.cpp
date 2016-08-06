#include "RemoveableComponent.hpp"

RemoveableComponent::RemoveableComponent(float time)
{
	setRemainTime(time);
}

RemoveableComponent::~RemoveableComponent()
{
}

float RemoveableComponent::getRemainTime()
{
	return mTime;
}

void RemoveableComponent::setRemainTime(float time)
{
	this->mTime = time;
}
