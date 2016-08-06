#include "TimeComponent.hpp"

TimeComponent::TimeComponent() : artemis::Component()
{
	setCurrentTime(2);
	setMaxTime(2);
}

void TimeComponent::setCurrentTime(float currentTime)
{
	this->mCurrent = currentTime;
}

void TimeComponent::setMaxTime(float mMaxTime)
{
	this->mMax = mMaxTime;
}

void TimeComponent::setDirty(bool dirty)
{
	this->mDirty = mDirty;

}

void TimeComponent::setActive(bool active)
{
	this->mActive = active;
}

bool TimeComponent::isDirty()
{
	return this->mDirty;
}

bool TimeComponent::isActive()
{
	return this->mActive;
}

float TimeComponent::getCurrentTime()
{
	return mCurrent;
}

float TimeComponent::getMaxTime()
{
	return mMax;
}

void TimeComponent::cloneFrom(TimeComponent * timeComponent)
{
	this->setCurrentTime(timeComponent->getCurrentTime());
	this->setMaxTime(timeComponent->getMaxTime());
	this->setDirty(timeComponent->isDirty());
	this->setActive(timeComponent->isActive());
}
